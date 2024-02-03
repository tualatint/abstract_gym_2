#include "two_joint_robot.h"
#include <iostream>

TwoJointRobot::TwoJointRobot(double l1, double l2)
    : l1_(l1)
    , l2_(l2)
{
    // Initialize the state or any other necessary variables
    reset();
}

void TwoJointRobot::initialize(const State& initialState)
{
    state_ = initialState;
}

void TwoJointRobot::step(const Action& action)
{
    // Update the joint angles based on the action
    state_.joint1 += action.joint1;
    state_.joint2 += action.joint2;
    forwardKinematics();
}
void TwoJointRobot::forwardKinematics()
{
    // Calculate the end-effector's position using inverse kinematics
    state_.theta = 0.0;
    double cos1 = cos(state_.joint1);
    double sin1 = sin(state_.joint1);
    double cos2 = cos(state_.joint1 + state_.joint2);
    double sin2 = sin(state_.joint1 + state_.joint2);

    state_.elbow_x = l1_ * cos1;
    state_.elbow_y = l1_ * sin1;

    state_.x = state_.elbow_x + l2_ * cos2;
    state_.y = state_.elbow_y + l2_ * sin2;
}

const State&
TwoJointRobot::getState() const
{
    return state_;
}

void TwoJointRobot::reset()
{
    // Set the robot to its initial state with joint angles at 0 and end-effector
    // at (l1 + l2, 0)
    state_.x = l1_ + l2_; // End-effector at (l1 + l2) in the x-direction
    state_.y = 0.0; // End-effector at 0 in the y-direction
    state_.theta = 0.0; // Orientation at 0 radians (facing the positive x-axis)
    state_.joint1 = 0.0; // First joint angle at 0 radians
    state_.joint2 = 0.0; // Second joint angle at 0 radians
    state_.elbow_x = l1_;
    state_.elbow_y = 0;
}

void TwoJointRobot::setState(const State& state)
{
    state_ = state;
}

void TwoJointRobot::printState() const
{
    std::cout << "State:\nx=" << state_.x 
    << ", y=" << state_.y 
    << ", theta=" << state_.theta
    << ", elbow_x=" << state_.elbow_x
    << ", elbow_y=" << state_.elbow_y
    << ", joint1=" << state_.joint1
    << ", joint2=" << state_.joint2 << std::endl;
}
