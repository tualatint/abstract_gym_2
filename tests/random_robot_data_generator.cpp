#include "datatype/robot_data.pb.h"
#include "utils/redis_dataframe_manager.h"
#include <chrono>
#include <hiredis/hiredis.h>
#include <iostream>
#include <random>
#include <uuid/uuid.h>

RobotData
generateRandomRobotData()
{
    RobotData robot_data;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(
        -3.14, 3.14); // 假设关节位置范围为-3.14到3.14
    for (int i = 0; i < 2; ++i) {
        robot_data.add_joint_positions(dis(gen));
    }

    for (int i = 0; i < 2; ++i) {
        robot_data.add_joint_actions(dis(gen));
    }

    for (int i = 0; i < 2; ++i) {
        robot_data.add_target_joint_positions(dis(gen));
    }

    robot_data.set_success_flag(rd() % 2 == 0);
    robot_data.set_collision_flag(rd() % 2 == 0);

    return robot_data;
}

int main()
{
    RedisDataFrameManager manager("127.0.0.1", 6379);

    for (auto i = 0; i < 1; i++) {
        RobotData random_robot_data = generateRandomRobotData();
        manager.storeDataFrame(random_robot_data.SerializeAsString());
    }

    // auto retrieved_data_frames = manager.getDataFramesByGlobalIndex(0,
    // std::numeric_limits<int>::max()); for (const auto& data_frame :
    // retrieved_data_frames) {
    //     RobotData retrieved_robot_data;
    //     retrieved_robot_data.ParseFromString(data_frame);
    //     std::cout<<"----"<<std::endl;
    //     for (float joint_position : retrieved_robot_data.joint_positions()) {
    //         std::cout << "Retrieved joint position: " << joint_position <<
    //         std::endl;
    //     }
    // }

    int batchSize = 3;
    auto random_data_frames = manager.getRandomBatchDataFrames(batchSize);
    for (const auto& data_frame : random_data_frames) {
        RobotData retrieved_robot_data;
        retrieved_robot_data.ParseFromString(data_frame);
        std::cout << "----" << std::endl;
        for (float joint_position : retrieved_robot_data.joint_positions()) {
            std::cout << "Retrieved joint position: " << joint_position << std::endl;
        }
    }

    return 0;
}