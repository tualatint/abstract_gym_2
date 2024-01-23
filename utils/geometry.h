#include <iostream>
#include <cmath>
#include <vector>

class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

double euclidean_distance(const Point& p0, const Point& p1) {
    return sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2));
}

double euclidean_distance_square(const Point& p0, const Point& p1) {
    return pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2);
}

class Line {
private:
    Point p0, p1;
    double max_x,min_x,max_y,min_y;

public:
    Line(const Point& p0, const Point& p1) : p0(p0), p1(p1) {
        max_x = std::max(p0.x, p1.x);
        min_x = std::min(p0.x, p1.x);
        max_y = std::max(p0.y, p1.y);
        min_y = std::min(p0.y, p1.y);
    }

    double length() {
        Point vec = {p1.x - p0.x, p1.y - p0.y};
        return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
    }

    std::vector<double> compute_line_function() {
        std::vector<double> result;
        // Assuming the line is not vertical or horizontal
        double a, b, c;
        if (p0.x == p1.x) { // vertical line
            a = 1;
            b = 0;
            c = -p0.x;
        } else if (p0.y == p1.y) { // horizontal line
            a = 0;
            b = 1;
            c = -p0.y;
        } else {
            a = (p1.y - p0.y) / (p1.x - p0.x);
            b = -1 / (p1.x - p0.x);
            c = (p0.y - a * p0.x) / (p1.x - p0.x);
        }
        result.push_back(a);
        result.push_back(b);
        result.push_back(c);

        return result;
    }

    std::vector<Point> divide_into_point_set(int resolution) {
        if (resolution <= 2) {
            std::vector<Point> points = {p0, p1};
            return points;
        }
        std::vector<Point> point_set;
        double step_x = (p1.x - p0.x) / (resolution - 1);
        double step_y = (p1.y - p0.y) / (resolution - 1);
        for (int i = 0; i <= resolution; ++i) {
            double x = p0.x + i * step_x;
            double y = p0.y + i * step_y;
            point_set.push_back({x, y});
        }
        return point_set;
    }

    Point normalized_line_vec() {
        Point vec = {p1.x - p0.x, p1.y - p0.y};
        double norm = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
        vec.x /= norm;
        vec.y /= norm;
        return vec;
    }

    Point normalized_perpendicular_vec() {
        Point vec = {p1.y - p0.y, -(p1.x - p0.x)};
        double norm = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
        vec.x /= norm;
        vec.y /= norm;
        return vec;
    }
    // Other members as needed
};
// Square class implementation would be similar, using the same Point class and math operations.

