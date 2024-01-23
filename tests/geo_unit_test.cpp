#include <gtest/gtest.h>
#include "utils/geometry.h" // Make sure to include the header file for your Line class

TEST(LineTest, Length) {
    Point p0(0, 0);
    Point p1(3, 4);
    Line line(p0, p1);

    EXPECT_NEAR(line.length(), 5.0, 1e-6); // Allow a small margin of error
}

TEST(LineTest, ComputeLineFunction) {
    Point p0(0, 0);
    Point p1(1, 1);
    Line line(p0, p1);

    auto line_function = line.compute_line_function();
    EXPECT_NEAR(line_function[0], 1.0, 1e-6);
    EXPECT_NEAR(line_function[1], -1.0, 1e-6);
    EXPECT_NEAR(line_function[2], 0.0, 1e-6);
}

TEST(LineTest, DivideIntoPointSet) {
    Point p0(0, 0);
    Point p1(3, 4);
    Line line(p0, p1);

    std::vector<Point> points = line.divide_into_point_set(10);
    EXPECT_EQ(points.size(), 11); // 10 divisions + start and end points

    // You can add more tests to check the actual points if needed
}

// Add more tests for other methods as needed

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}