#include <opencv2/opencv.hpp>
#include <cmath>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <vector>  

#include "TwoJointRobot.h"

class RobotVisualizer {
public:
    RobotVisualizer(int canvasWidth, int canvasHeight)
        : canvasWidth_(canvasWidth), canvasHeight_(canvasHeight) {}

    void visualize(const TwoJointRobot& robot) {
        cv::Mat canvas(canvasHeight_, canvasWidth_, CV_8UC3, cv::Scalar(0, 0, 0));

        // Get the state of the robot
        const State& state = robot.getState();
        // Calculate the scaling factor and the center position
        maxReach_ = robot.getL1() + robot.getL2();
        scaleFactor_ = canvasWidth_ / (3 * maxReach_);
        cv::Point2d center(canvasWidth_ / 2.0, canvasHeight_ / 2.0);

        // Draw the end-effector and elbow
        cv::Point2d pix_elbow = cv::Point(state.elbow_x * scaleFactor_ + center.x, state.elbow_y * scaleFactor_ + center.y);
        cv::Point2d pix_ee = cv::Point(state.x * scaleFactor_ + center.x, state.y * scaleFactor_ + center.y);
        cv::Point2d pix_base = cv::Point(0,0);

        // link 1
        cv::line(canvas, cv::Point(center.x, center.y), pix_elbow, cv::Scalar(0, 255, 0), 2);
        // link 2
        cv::line(canvas, pix_elbow, pix_ee, cv::Scalar(0, 255, 255), 2);

        cv::circle(canvas, pix_base, 5, cv::Scalar(255, 255, 255), -1); 
        cv::circle(canvas, pix_ee, 5, cv::Scalar(0, 0, 255), -1); 
        cv::circle(canvas, pix_elbow, 5, cv::Scalar(255, 255, 0), -1);

        drawRadiusCircle(canvas);
        // Display the canvas
        cv::namedWindow("Robot Visualization", cv::WINDOW_NORMAL);
        cv::imshow("Robot Visualization", canvas);
        cv::waitKey(0);
    }

        void drawRadiusCircle(cv::Mat& canvas) {
        cv::Point2d center(canvas.cols / 2.0, canvas.rows / 2.0);
        int num_points = 360; // Number of points to approximate the circle
        int radius = (int)(scaleFactor_ * maxReach_);
        // Create a vector to store the points
        std::vector<cv::Point> points(num_points);
        // Calculate the points around the circle's perimeter
        for (int i = 0; i < num_points; ++i) {
            double angle = (i * CV_PI / 180); // Convert degrees to radians
            points[i] = cv::Point(center.x + radius * cos(angle), center.y + radius * sin(angle));
        }
        int thickness = 1;
        int lineType = 8; // 8 for dashed line 
        cv::Scalar color = cv::Scalar(255, 255, 255);
        // Draw the dashed circle using polylines
        cv::polylines(canvas, points, true, color, 1, cv::LINE_AA);
        // cv::circle(canvas, center, scaleFactor_ * maxReach_, cv::Scalar(0, 255, 0), thickness, lineType, 0);
    }

private:
    int canvasWidth_;
    int canvasHeight_;
    double maxReach_;
    double scaleFactor_;
};

int main() {
    srand(time(nullptr)); // Seed the random number generator
    TwoJointRobot robot(0.4, 0.3); // Initialize the robot with link lengths
    robot.reset(); // Reset the robot to its initial state

    // Create a RobotVisualizer with a larger canvas size
    RobotVisualizer visualizer(1200, 800); // canvasWidth, canvasHeight

    // Visualize the robot
    visualizer.visualize(robot);
    // Run the simulation for a certain number of steps
    const int numSteps = 100;
    for (int step = 0; step < numSteps; ++step) {
        robot.applyRandomAction(); // Apply a random action to the robot
        visualizer.visualize(robot); // Visualize the robot's current state
        cv::waitKey(0); // Wait for a short time to see the visualization
    }

    return 0;
}