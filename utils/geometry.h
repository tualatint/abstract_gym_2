#include <cmath>
#include <vector>

class Point {
public:
    double x, y;
    Point(double x, double y)
        : x(x)
        , y(y)
    {
    }
};

double euclidean_distance(const Point& p0, const Point& p1)
{
    return sqrt(pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2));
}

double euclidean_distance_square(const Point& p0, const Point& p1)
{
    return pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2);
}

class Line {
private:
    Point p0, p1;
    double max_x, min_x, max_y, min_y;

public:
    Line(const Point& p0, const Point& p1)
        : p0(p0)
        , p1(p1)
    {
        max_x = std::max(p0.x, p1.x);
        min_x = std::min(p0.x, p1.x);
        max_y = std::max(p0.y, p1.y);
        min_y = std::min(p0.y, p1.y);
    }
    Point getP0() const { return p0; }
    Point getP1() const { return p1; }
    // Getters for max_x, min_x, max_y, min_y
    double getMaxX() const { return max_x; }
    double getMinX() const { return min_x; }
    double getMaxY() const { return max_y; }
    double getMinY() const { return min_y; }

    // Setters for p0 and p1
    void setP0(const Point& newP0) { p0 = newP0; }
    void setP1(const Point& newP1) { p1 = newP1; }

    double length()
    {
        return euclidean_distance(p0, p1);
    }

    std::vector<double> compute_line_function()
    {
        // The function of the line should be in this form: ax + by + c = 0
        // :return: a, b, c
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
            a = 1.0 / (p1.x - p0.x);
            b = -1.0 / (p1.y - p0.y);
            c = p0.y / (p1.y - p0.y) - p0.x / (p1.x - p0.x);
        }
        result.push_back(a);
        result.push_back(b);
        result.push_back(c);

        return result;
    }

    std::vector<Point> divide_into_point_set(int resolution)
    {
        if (resolution <= 2) {
            std::vector<Point> points = { p0, p1 };
            return points;
        }
        std::vector<Point> point_set;
        double step_x = (p1.x - p0.x) / (resolution - 1);
        double step_y = (p1.y - p0.y) / (resolution - 1);
        for (int i = 0; i <= resolution; ++i) {
            double x = p0.x + i * step_x;
            double y = p0.y + i * step_y;
            point_set.push_back({ x, y });
        }
        return point_set;
    }

    Point normalized_line_vec()
    {
        Point vec = { p1.x - p0.x, p1.y - p0.y };
        double norm = this->length();
        vec.x /= norm;
        vec.y /= norm;
        return vec;
    }

    Point normalized_perpendicular_vec()
    {
        Point vec = { p1.y - p0.y, -(p1.x - p0.x) };
        double norm = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
        vec.x /= norm;
        vec.y /= norm;
        return vec;
    }
    // Other members as needed
};

class Square {
    // Define the square using two corner points
    // :param pbl: bottom left
    // :param pur: upper right
private:
    Point pbl, pur;
    Point center;

public:
    Square(const Point& pbl, const Point& pur)
        : pbl(pbl)
        , pur(pur)
        , center((pbl.x + pur.x) / 2.0, (pbl.y + pur.y) / 2.0)
    {
    }
    // Getters for pbl, pur, and center
    Point getPBL() const { return pbl; }
    Point getPUR() const { return pur; }
    Point getCenter() const { return center; }
    //get maxx
    double getMaxX() const { return std::max(pbl.x, pur.x); }
    //get maxy
    double getMaxY() const { return std::max(pbl.y, pur.y); }
    //get minx
    double getMinX() const { return std::min(pbl.x, pur.x); }
    //get miny
    double getMinY() const { return std::min(pbl.y, pur.y); }

    // Setters for pbl and pur (you might not need setters for these, as they are usually set once at construction)
    void setPBL(const Point& newPBL) { pbl = newPBL; }
    void setPUR(const Point& newPUR) { pur = newPUR; }
};