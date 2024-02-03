#include "utils/geometry.h"
#include <iostream>

int main()
{
    // Example usage:
    Point p0(0, 0);
    Point p1(1, 1);
    Line line(p0, p1);

    std::cout << "Line length: " << line.length() << std::endl;
    auto line_function = line.compute_line_function();
    std::cout << "Line function coefficients: a = " << line_function[0]
              << ", b = " << line_function[1] << ", c = " << line_function[2]
              << std::endl;

    return 0;
}