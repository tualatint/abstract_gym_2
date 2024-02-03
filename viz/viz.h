#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

#include "env/env.h"
#include "robot/two_joint_robot.h"

class RobotVisualizer {
public:
    RobotVisualizer(int canvasWidth, int canvasHeight, RobotEnvironment& env, TwoJointRobot& robot)
        : canvasWidth_(canvasWidth)
        , canvasHeight_(canvasHeight)
        , env_(env)
        , robot_(robot)
    {
    }

    void drawEnvironment(cv::Mat& canvas)
    {
        int rows = env_.getHeight();
        int cols = env_.getWidth();
        int cent_x = canvas.cols / 2;
        int cent_y = canvas.rows / 2;
        int cellSize = (int)(scaleFactor_ * env_.getScale()); // Size of each cell in pixels            
        // int cellSize = canvas.rows / rows; // Size of each cell in pixels           
        int x_shift = canvas.cols / 2 - cellSize * cols / 2; //in pixels
        int y_shift = canvas.rows / 2 - cellSize * rows / 2;

        // Draw the obstacles
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (env_.getEnvironment()[y][x] == 1) {
                    cv::rectangle(canvas, cv::Point(x * cellSize + x_shift, y * cellSize + y_shift),
                        cv::Point((x + 1) * cellSize + x_shift, (y + 1) * cellSize + y_shift),
                        cv::Scalar(100, 100, 100), -1);
                }
            }
        }
    }

    void drawRobot(cv::Mat& canvas)
    {
        // Get the state of the robot
        const State& state = robot_.getState();
        // robot_.printState();
        // Calculate the scaling factor and the center position
        maxReach_ = robot_.getL1() + robot_.getL2(); // in meters
        scaleFactor_ = canvasHeight_ / (2 * maxReach_); // pixels per meter.
        cv::Point2d center(canvasWidth_ / 2.0, canvasHeight_ / 2.0);

        // Draw the end-effector and elbow
        cv::Point2d pix_elbow = cv::Point(state.elbow_x * scaleFactor_ + center.x,
            -state.elbow_y * scaleFactor_ + center.y);
        cv::Point2d pix_ee = cv::Point(state.x * scaleFactor_ + center.x,
            -state.y * scaleFactor_ + center.y);
        cv::Point2d pix_base = cv::Point(0, 0);

        // link 1
        cv::line(canvas,
            cv::Point(center.x, center.y),
            pix_elbow,
            cv::Scalar(0, 255, 0),
            2);
        // link 2
        cv::line(canvas, pix_elbow, pix_ee, cv::Scalar(0, 255, 255), 2);

        cv::circle(canvas, pix_base, 5, cv::Scalar(255, 255, 255), -1);
        cv::circle(canvas, pix_ee, 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(canvas, pix_elbow, 5, cv::Scalar(255, 255, 0), -1);
    }

    void visualize()
    {
        cv::Mat canvas(canvasHeight_, canvasWidth_, CV_8UC3, cv::Scalar(0, 0, 0));

        drawRobot(canvas);
        drawEnvironment(canvas);
        drawRadiusCircle(canvas);
        drawTarget(canvas);

        // Display the canvas
        cv::namedWindow("Robot Visualization", cv::WINDOW_NORMAL);
        cv::imshow("Robot Visualization", canvas);
        cv::waitKey(1);
    }

    void drawRadiusCircle(cv::Mat& canvas)
    {
        cv::Point2d center(canvas.cols / 2.0, canvas.rows / 2.0);
        int num_points = 360; // Number of points to approximate the circle
        int radius = (int)(scaleFactor_ * maxReach_);
        // Create a vector to store the points
        std::vector<cv::Point> points(num_points);
        // Calculate the points around the circle's perimeter
        for (int i = 0; i < num_points; ++i) {
            double angle = (i * CV_PI / 180); // Convert degrees to radians
            points[i] = cv::Point(center.x + radius * cos(angle),
                center.y + radius * sin(angle));
        }
        int thickness = 1;
        int lineType = 8; // 8 for dashed line
        cv::Scalar color = cv::Scalar(255, 255, 255);
        // Draw the dashed circle using polylines
        cv::polylines(canvas, points, true, color, 1, cv::LINE_AA);
    }

    void setTarget(double x, double y)
    {
        target_ = cv::Point2d(x, y);
    }

    void drawTarget(cv::Mat& canvas)
    {        
        target_pixel_ = cv::Point2d(target_.x * scaleFactor_ + canvas.cols / 2.0,
            -target_.y * scaleFactor_ + canvas.rows / 2.0);
        cv::circle(canvas, target_pixel_, 5, cv::Scalar(0, 0, 255), -1, cv::LINE_AA);
    }

private:
    int canvasWidth_;
    int canvasHeight_;
    double maxReach_;
    double scaleFactor_;
    cv::Point2d target_; // in robot frame in meters
    cv::Point2d target_pixel_;
    RobotEnvironment& env_;
    TwoJointRobot& robot_;
};
