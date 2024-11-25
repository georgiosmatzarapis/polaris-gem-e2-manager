// author: georgiosmatzarapis

#include <ros/ros.h>
#include <std_msgs/Bool.h>

#include "ros1_lib/publisher.hpp"

int main(int argc, char** argv) {
  ros::init(argc, argv, "emergency_stop_node");

  ros1_lib::Publisher<std_msgs::Bool> emergencyButtonPublisher{
      "/gem_manager/emergency_button", 1000};

  ros::Rate loopRate{1};

  ROS_INFO("Emergency-stop node started");

  bool emergencyPressed{false};
  const ros::Time startTime{ros::Time::now()};

  while (ros::ok()) {
    std_msgs::Bool emergencyButtonMsg;

    if (ros::Time::now() - startTime > ros::Duration(15.0) &&
        !emergencyPressed) {
      emergencyButtonMsg.data = 1;
      emergencyPressed = true;
      ROS_WARN("Emergency Stop Triggered!");
    } else {
      emergencyButtonMsg.data = 0;
    }

    emergencyButtonPublisher.publish(emergencyButtonMsg);

    ros::spinOnce();
    loopRate.sleep();
  }

  return 0;
}
