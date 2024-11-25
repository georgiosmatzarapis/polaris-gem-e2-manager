// author: georgiosmatzarapis

#include <ros/ros.h>

#include "gem_state_manager/callback_handlers.hpp"
#include "gem_state_manager/state_manager.hpp"

int main(int argc, char** argv) {
  try {
    ros::init(argc, argv, "gem_state_manager");
    ros::NodeHandle nodeHandle{};

    gem_state_manager::CallbackHandlers callbackHandlers{nodeHandle};
    gem_state_manager::StateManager stateManager{nodeHandle, callbackHandlers};

    ROS_INFO("State-manager node started");

    ros::AsyncSpinner spinner(4);
    spinner.start();

    stateManager.checkVehicleAndColdStart();

    ros::waitForShutdown();
  } catch (const std::exception& exception) {
    ROS_ERROR("Exception: %s", exception.what());
    return 1;
  }

  return 0;
}
