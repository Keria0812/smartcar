#include <ros/ros.h>

#include "dynamic_routing.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "dynamic_routing");
    Dynamic_routing Dynamic_routing;

    while (ros::ok()) {
      ros::waitForShutdown();
      std::cout << "close node." << std::endl;
    }
    return 0;
}