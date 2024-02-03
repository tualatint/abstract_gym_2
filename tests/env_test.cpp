#include "env/env.h"
#include <iostream>

int main()
{
    try {
        RobotEnvironment env("env_conf.txt");
        int width = env.getWidth();
        int height = env.getHeight();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << (env.isObstacle(j, i) ? '1' : '0') << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }

    return 0;
}