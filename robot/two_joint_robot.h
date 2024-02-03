#ifndef TWO_JOINT_ROBOT_H
#define TWO_JOINT_ROBOT_H

#include <cmath>
#include <cstdlib> // For rand() and srand()
#include <random>

// Define the action space for the robot
struct Action {
    double joint1; // Action for the first joint
    double joint2; // Action for the second joint
};

// Define the state space for the robot
struct State {
    double x; // x-coordinate of the end-effector
    double y; // y-coordinate of the end-effector
    double theta; // Orientation of the end-effector (in radians)
    double joint1; // Angle of the first joint (in radians)
    double joint2; // Angle of the second joint (in radians)
    double elbow_x; // x-coordinate of the elbow (midpoint between joints)
    double elbow_y; // y-coordinate of the elbow (midpoint between joints)
};

class TwoJointRobot {
public:
    TwoJointRobot(double l1 = 0.4,
        double l2 = 0.3); // Constructor with link lengths

    // Initialize the robot with starting state
    void initialize(const State& initialState);

    // Apply an action to the robot and update its state
    void step(const Action& action);

    // Get the current state of the robot
    const State& getState() const;
    void setState(const State& newState);
    void forwardKinematics();
    void inverseKinematics(const State& targetState);
    void printState() const;

    // Reset the robot to its initial state
    void reset();

    // Getter methods for the state
    double getX() const { return state_.x; }
    double getY() const { return state_.y; }
    double getTheta() const { return state_.theta; }
    double getJoint1() const { return state_.joint1; }
    double getJoint2() const { return state_.joint2; }

    double getL1() const { return l1_; }
    double getL2() const { return l2_; }

    // Other methods for interacting with the environment can be added here
    void applyRandomAction()
    {
        auto act = sampleRandomAction();
        step(act);
    }
    
    State sampleRandomState()
    {
        State state;
        state.theta = 0.0;
        // state.joint1 = (double)(rand() % 1000) / 1000.0*2 * M_PI; // Random
        // state.joint2 = (double)(rand() % 1000) / 1000.0*2 * M_PI; // Random
        std::random_device rd;
        std::mt19937 rng(rd());; // Mersenne Twister random number generator
        std::uniform_real_distribution<double> dist(-1.0, 1.0); // Uniform distribution between -0.01 and 0.01
        state.joint1 = dist(rng) *  M_PI; 
        state.joint2 = dist(rng) *  M_PI;
        double cos1 = cos(state.joint1);
        double sin1 = sin(state.joint1);
        double cos2 = cos(state.joint1 + state.joint2);
        double sin2 = sin(state.joint1 + state.joint2);

        state.elbow_x = l1_ * cos1;
        state.elbow_y = l1_ * sin1;

        state.x = state.elbow_x + l2_ * cos2;
        state.y = state.elbow_y + l2_ * sin2;

        return state;
    }
    
    Action sampleRandomAction(double action_scale = 0.05)
    {   
        std::random_device rd;
        std::mt19937 rng(rd());; // Mersenne Twister random number generator
        std::uniform_real_distribution<double> dist(-action_scale, action_scale); // Uniform distribution between -0.01 and 0.01
        Action act;
        act.joint1 = dist(rng);
        act.joint2 = dist(rng);
        return act;
    }

private:
    State state_; // Current state of the robot
    double l1_; // Length of the first link
    double l2_; // Length of the second link
};

#endif // TWO_JOINT_ROBOT_H