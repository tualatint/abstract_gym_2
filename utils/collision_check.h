#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

#include "env/env.h"
#include "geometry.h"
#include "robot/two_joint_robot.h"

//Checks whether a line and a square is in collision
class CollisionChecker {
private:
    Line line;
    Square square;
    std::tuple<double, double, double> line_func;

public:
    CollisionChecker(Line& line, const Square& square)
        : line(line)
        , square(square)
    {
        // The function of the line should be in this form: ax + by + c = 0
        auto func = line.compute_line_function();
        line_func = std::make_tuple(func[0], func[1], func[2]);
    }

    double static compute_lambda(double x, Line line)
    {
        return (x - line.getMinX()) / (line.getMaxX() - line.getMinX());
    }

    bool AABB_collision_check() const
    {
        // Check if the square and the line intersect.
        if (square.getMaxX() < line.getMinX() || square.getMinX() > line.getMaxX() || square.getMaxY() < line.getMinY() || square.getMinY() > line.getMaxY()) {
            return false; // not in collision
        }
        return true; // maybe in collision
    }

    //compute the value of the line function at the 4 corners of the square.
    std::vector<double> compute_corner_line_value() const
    {
        std::vector<double> v(4);

        v[0] = std::get<0>(line_func) * square.getPBL().x + std::get<1>(line_func) * square.getPBL().y + std::get<2>(line_func);
        v[1] = std::get<0>(line_func) * square.getPBL().x + std::get<1>(line_func) * square.getPUR().y + std::get<2>(line_func);
        v[2] = std::get<0>(line_func) * square.getPUR().x + std::get<1>(line_func) * square.getPBL().y + std::get<2>(line_func);
        v[3] = std::get<0>(line_func) * square.getPUR().x + std::get<1>(line_func) * square.getPUR().y + std::get<2>(line_func);
        return v;
    }

    bool collision_check() const
    {
        if (AABB_collision_check() == false) // not in collision
        {
            return false;
        }
        auto vec = compute_corner_line_value();

        size_t pos_count = std::count_if(vec.begin(), vec.end(), [](double v) { return v > 0; });
        size_t neg_count = std::count_if(vec.begin(), vec.end(), [](double v) { return v < 0; });

        if (pos_count > 0 && neg_count > 0) {
            return check_sections();
        } else {
            return false; // not in collision
        }
    }

    bool check_sections() const
    {
        double a = std::get<0>(line_func);
        double b = std::get<1>(line_func);
        double c = std::get<2>(line_func);

        double sx_y_min = (-c - b * square.getMinY()) / a;
        Point p1(sx_y_min, square.getMinY());
        double sx_y_max = (-c - b * square.getMaxY()) / a;
        Point p2(sx_y_max, square.getMaxY());
        double sy_x_min = (-c - a * square.getMinX()) / b;
        Point p3(square.getMinX(), sy_x_min);
        double sy_x_max = (-c - a * square.getMaxX()) / b;
        Point p4(square.getMaxX(), sy_x_max);
        Point pl[] = { p1, p2, p3, p4 };
        std::sort(std::begin(pl), std::end(pl), [](const Point& p1, const Point& p2) { return p1.x < p2.x; });
        double lam1 = compute_lambda(pl[1].x, line);
        double lam2 = compute_lambda(pl[2].x, line);
        double epsilon = 1e-10;
        if ((1.0 > lam1 && lam1 > epsilon) || (1.0 > lam2 && lam2 > epsilon)) {
            return true;
        } else {
            return false;
        }
    }
};
