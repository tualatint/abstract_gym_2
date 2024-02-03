#include "env/env.h"
#include "robot/two_joint_robot.h"
#include "viz/viz.h"
#include "utils/collision_detector.h"
#include <stdlib.h>

int main()
{
    srand(time(nullptr)); // Seed the random number generator
    TwoJointRobot robot(0.4, 0.3); // Initialize the robot with link lengths
    robot.reset(); // Reset the robot to its initial state
    RobotEnvironment env("env_conf.txt");
    // Create a RobotVisualizer with a larger canvas size
    RobotVisualizer visualizer(800, 800, env,robot); // canvasWidth, canvasHeight
    CollisionDetector detector(env,robot);
    // Visualize the robot
    visualizer.visualize();
    // Run the simulation for a certain number of steps
    const int numSteps = 1000;
    for (int step = 0; step < numSteps; ++step) {
        auto action = robot.sampleRandomAction();
        robot.step(action); // Apply a random action to the robot
        visualizer.visualize(); // Visualize the robot's current state
        if(detector.isColliding())
        {
            std::cout<<"Collision Detected."<<std::endl;
        }
        cv::waitKey(1); // Wait for a short time to see the visualization
    }

    return 0;
}