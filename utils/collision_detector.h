#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "env/env.h"
#include "robot/two_joint_robot.h"
#include "utils/collision_check.h"

// Detect the collision between robot and environment obstacles.
class CollisionDetector {
public:
    CollisionDetector(const RobotEnvironment& env, const TwoJointRobot& robot)
        : environment_(env), robot_(robot) {}

    bool isColliding() {
        const auto& state = robot_.getState();
        // Calculate the position of the end effector
        double endEffectorX = state.x;
        double endEffectorY = state.y;

        // Calculate the position of the elbow
        double elbowX = state.elbow_x;
        double elbowY = state.elbow_y;
        Line upper_arm = Line(Point(0,0), Point(elbowX, elbowY));
        Line forearm = Line(Point(elbowX, elbowY), Point(endEffectorX, endEffectorY));

        // Iterate over all obstacles in the environment
        for (int y = 0; y < environment_.getHeight(); ++y) {
            for (int x = 0; x < environment_.getWidth(); ++x) {
                if (environment_.getEnvironment()[y][x] == 1) {
                    // Calculate the corners of the square obstacle
                    double obstacleX1 = (x - environment_.getWidth() / 2.0)*environment_.getScale();
                    double obstacleY1 = -(y - environment_.getHeight() / 2.0)*environment_.getScale();
                    double obstacleX2 = obstacleX1 + environment_.getScale();
                    double obstacleY2 = obstacleY1 - environment_.getScale();
                    auto s = Square(Point(obstacleX1, obstacleY1), Point(obstacleX2, obstacleY2));
                    
                    CollisionChecker checker0(upper_arm, s);
                    CollisionChecker checker1(forearm, s);
                    // Check for collision with the obstacle
                    if (checker0.collision_check()||checker1.collision_check()){
                        return true;
                    }
                }
            }
        }
        return false; // No collision detected
    }

private:
    const RobotEnvironment& environment_;
    const TwoJointRobot& robot_;

};

#endif