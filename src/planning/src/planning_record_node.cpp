#include <ros/ros.h>

#include "planning_record.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "planning_record");
    PlanningRecord planningpecord;

    while (ros::ok()) {
      ros::waitForShutdown();
      std::cout << "close node." << std::endl;
    }
    return 0;
}