#include "gym.h"

int main() {
    GymManager manager("gym_config.yaml");

    manager.startSimulations();
    manager.joinThreads();

    return 0;
}