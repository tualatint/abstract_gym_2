#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <datatype/robot_data.pb.h>
#include "env/env.h"
#include "robot/two_joint_robot.h"
#include "viz/viz.h"
#include "utils/collision_detector.h"
#include "utils/redis_dataframe_manager.h"
#include "utils/zmq_class.h"
#include "yaml-cpp/yaml.h"  // or another YAML parser library


class Gym {
public:
    Gym(const std::string& configFilePath, int idx)
    :idx_(idx)
    {
        // Load the configuration
        YAML::Node config = YAML::LoadFile(configFilePath);
        visualization_ = config["visualization"].as<bool>();
        maxNumSteps_ = config["max_num_steps_per_run"].as<int>();
        auto robot_upper_arm = config["robot_upper_arm"].as<double>();
        auto robot_forearm = config["robot_forearm"].as<double>();
        target_EE_pos_ = config["target_position"].as<std::vector<double>>();//EE target pos
        epsilon_ = config["epsilon"].as<double>();
        auto host = config["redis_host"].as<std::string>();
        auto port = config["redis_port"].as<int>();
        auto zmq_port = config["zmq_port"].as<int>();
        auto zmq_ip = config["zmq_ip"].as<std::string>();
        auto ring_buffer_size = config["ring_buffer_size"].as<int64_t>();
        max_run_ = config["max_run"].as<int>();
        explore_rate_= config["explore_rate"].as<double>();
        online_q_learning_ = 
            config["online_q_learning"].as<bool>();
        gamma_ = config["gamma"].as<float>(); // reward decay rate in Q value calculation
        action_scale_= config["action_scale"].as<double>();
        environment_ = std::make_unique<RobotEnvironment>("env_conf.txt");
        robot_ = std::make_unique<TwoJointRobot>(robot_upper_arm, robot_forearm);
        if (visualization_)
        {
            visualizer_ = std::make_unique<RobotVisualizer>(800, 800, *environment_, *robot_);
            visualizer_->setTarget(target_EE_pos_[0], target_EE_pos_[1]);
        }

        collisionDetector_ = 
            std::make_unique<CollisionDetector>(*environment_, *robot_);
        redis_ = std::make_unique<RedisDataFrameManager>(host,port,ring_buffer_size);
        zmq_ = 
            std::make_unique<ZmqCppCommunication>(zmq_ip,zmq_port);
    }

    void resetToRandomState()
    {
        auto state = robot_->sampleRandomState();
        robot_->setState(state);
        while(collisionDetector_->isColliding())
        {
            state = robot_->sampleRandomState();
            robot_->setState(state);
        }
    }

    RobotData step(Action& action) {

        RobotData dataFrame;
        const auto& state = robot_->getState();        
        dataFrame.add_joint_positions(state.joint1); // before motion
        dataFrame.add_joint_positions(state.joint2);
        dataFrame.add_ee_positions(state.x);
        dataFrame.add_ee_positions(state.y);

        robot_->step(action);
        // robot_->printState();
        bool b_collision = collisionDetector_->isColliding();
        bool b_done = false;
        float reward = 0.0; // Calculate the reward

        dataFrame.add_joint_actions(action.joint1);
        dataFrame.add_joint_actions(action.joint2);

        dataFrame.add_target_ee_positions(target_EE_pos_[0]);
        dataFrame.add_target_ee_positions(target_EE_pos_[1]);
        dataFrame.set_collision_flag(b_collision);

        // Check for collision
        if (b_collision) {
            // Handle collision (e.g., reset the robot, apply a penalty)
            // std::cout << "Collision detected!" << std::endl;
            reward = -1e2;
            b_done = true;
            resetToRandomState();
        }

        //check whether the target is reached
        if (isTargetReached(state)) {
            // Handle target reached (e.g., apply a reward, reset the robot)
            std::cout << "Target reached!" << std::endl;
            reward = 1e2;
            b_done = true;
            resetToRandomState();
        }

        dataFrame.set_reward(reward);
        dataFrame.set_done_flag(b_done);

        return dataFrame;
    }

    bool isTargetReached(const State& state) {
        // Check if the robot is within a certain distance of the target
        if (std::abs(state.x - target_EE_pos_[0]) < epsilon_ &&
                std::abs(state.y - target_EE_pos_[1]) < epsilon_) {
                return true;
            }
        return false;
    }

    void start() {
        if (online_q_learning_)
            start_online_learning();
        else
            start_offline_learning();
    }

    void start_offline_learning() {
        std::cout<<"Thread "<<idx_<<" start offline learning"<<std::endl;
        for(int j=0; j<max_run_; j++)
        {
            resetToRandomState();
            RobotDataFrameList dataFrameList;
            for (int i = 0; i < maxNumSteps_; ++i) {
                auto action = robot_->sampleRandomAction(); 
                RobotData dataFrame = step(action);
                RobotData* df = dataFrameList.add_robot_data_frames();
                df->CopyFrom(dataFrame);
                if (dataFrame.done_flag()) {
                    break;
                }
                // Visualize the robot and environment if enabled
                if (visualization_) {
                    visualizer_->visualize();
                }
                // Process the data frame (e.g., update a policy or log the data)
                // ...
            }
            if (j%1000 == 0){
                std::cout<<"Thread "<<idx_<<" iter "<<j<<" saving data..."<<std::endl;
            }
            redis_->saveDataFrames(dataFrameList);
        }
        std::cout<<"Thread "<<idx_<<" finished"<<std::endl;
    }

    void start_online_learning() {
        std::cout<<"Thread "<<idx_<<" start online learning"<<std::endl;
        int action_candidate_num = 10;
        for(int j=0; j<max_run_; j++)
        {
            resetToRandomState();
            RobotDataFrameList dataFrameList;
            for (int i = 0; i < maxNumSteps_; ++i) {
                auto action = EpsilonGreedyPolicy(i);
                RobotData dataFrame = step(action);
                RobotData* df = dataFrameList.add_robot_data_frames();
                df->CopyFrom(dataFrame);
                if (dataFrame.done_flag()) {
                    std::cout<<"Thread "<<idx_<<" iter "<<j<<" done"<<std::endl;
                    break;
                }
                // Visualize the robot and environment if enabled
                if (visualization_) {
                    visualizer_->visualize();
                    // sleep(0.1);
                }
            }
            auto processed_dataFrameList = process_Q_data(dataFrameList);
            // processed p_ring_buff
            redis_->addDataToRingbuffer(processed_dataFrameList.SerializeAsString(),"p_ring_buff");  
            // original ring_buff
            redis_->addDataToRingbuffer(dataFrameList.SerializeAsString(),"ring_buff");            
            // redis_->saveDataFrames(dataFrameList);
        }
    }

    Action EpsilonGreedyPolicy(int i){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (dis(gen) < explore_rate_) {
            // 以探索概率explore_rate_选择随机动作
            auto act = robot_->sampleRandomAction(action_scale_);
            // std::cout<<"act "<<act.joint1<<" "<<act.joint2<<std::endl;
            return act;
        } else {
            // 以1-explore_rate_的概率选择具有最大动作值的动作
            RobotData data;
            data.add_joint_positions(robot_->getJoint1());
            data.add_joint_positions(robot_->getJoint2());
            if(i==0){
                data.set_done_flag(true); // using done flag to signal the beginning of an experiment
            }
            auto resp = zmq_->sendRobotData(data); //send the data to Q net
            data.ParseFromString(resp);
            Action action;
            action.joint1 = data.joint_actions(0);
            action.joint2 = data.joint_actions(1);

            return action;
        }
    }
    RobotDataFrameList process_Q_data(RobotDataFrameList& dataFrameList){
        RobotDataFrameList processed_dataFrameList;
        auto length = dataFrameList.robot_data_frames_size();
        if (length > 0) {
        // Iterate over each RobotData message in the list
            auto end_reword = dataFrameList.robot_data_frames(length - 1).reward();
            for (int i = 0; i < length; ++i) {
                const RobotData& frame = dataFrameList.robot_data_frames(i);
                RobotData processed_dataFrame(frame);
                auto reward = end_reword * pow(gamma_,length-i-1);
                processed_dataFrame.set_reward(reward);
                processed_dataFrameList.add_robot_data_frames()->CopyFrom(processed_dataFrame);
            }
        }
        return processed_dataFrameList;
    }

private:
    std::unique_ptr<RobotEnvironment> environment_;
    std::unique_ptr<TwoJointRobot> robot_;
    std::unique_ptr<RobotVisualizer> visualizer_;
    std::unique_ptr<CollisionDetector> collisionDetector_;
    std::unique_ptr<RedisDataFrameManager> redis_;
    std::unique_ptr<ZmqCppCommunication> zmq_;
    std::vector<double> target_EE_pos_;
    double explore_rate_ = 0.5; //explore random action rate
    double epsilon_;
    int maxNumSteps_;
    int max_run_; // max iter per thread
    bool visualization_;
    int idx_; //thread index
    bool online_q_learning_;
    double action_scale_;
    float gamma_;
};

class GymManager {
private:
    std::vector<std::thread> threads_;
    std::string configFilePath_;
    int instance_;

public:
    // for multithread management
    GymManager(std::string configFilePath)
    :configFilePath_(configFilePath) {
        YAML::Node config = YAML::LoadFile(configFilePath);
        instance_ = config["instance"].as<int>();
    }

    ~GymManager() {
        // Clean up Redis connection here
    }

    void startSimulations(int numInstances) {
        instance_ = numInstances;
        startSimulations();     
    }
    void startSimulations() {
        for (int i = 0; i < instance_; ++i) {
            threads_.push_back(std::thread([this, i] {
                auto gym = std::make_shared<Gym>(configFilePath_,i);
                gym->start();
            }));
        }
    }
    void joinThreads() {
        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }
};