#ifndef TWO_JOINT_ROBOT_H
#define TWO_JOINT_ROBOT_H

#include <cmath>
#include <cstdlib> // For rand() and srand()

// Define the action space for the robot
struct Action {
    double joint1; // Action for the first joint
    double joint2; // Action for the second joint
};

// Define the state space for the robot
struct State {
    double x;      // x-coordinate of the end-effector
    double y;      // y-coordinate of the end-effector
    double theta;  // Orientation of the end-effector (in radians)
    double joint1; // Angle of the first joint (in radians)
    double joint2; // Angle of the second joint (in radians)
    double elbow_x; // x-coordinate of the elbow (midpoint between joints)
    double elbow_y; // y-coordinate of the elbow (midpoint between joints)
};

class TwoJointRobot {
public:
    TwoJointRobot(double l1 = 0.4, double l2 = 0.3); // Constructor with link lengths

    // Initialize the robot with starting state
    void initialize(const State& initialState);

    // Apply an action to the robot and update its state
    void step(const Action& action);

    // Get the current state of the robot
    const State& getState() const;

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
    void applyRandomAction() {
        double randomAngle1 = (double)(rand() % 100) / 10000.0 * 2 * M_PI; // Random angle in radians
        double randomAngle2 = (double)(rand() % 100) / 10000.0 * 2 * M_PI; // Random angle in radians
        Action act;
        act.joint1 = randomAngle1;
        act.joint2 = randomAngle2;
        step(act);
    }

private:
    State state_; // Current state of the robot
    double l1_;    // Length of the first link
    double l2_;    // Length of the second link
};

#endif // TWO_JOINT_ROBOT_H