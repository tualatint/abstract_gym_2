#include "utils/collision_check.h"

int main()
{
    Point p0(0., 0.);
    Point p1(1., 2.);
    Line line(p0, p1);

    Point min_pt(0., 0.8);
    Point max_pt(0.9, 1.4);
    Square square(min_pt, max_pt);

    CollisionChecker cc(line, square);

    std::cout << "Collision check result: " << cc.collision_check() << std::endl;

    return 0;
}