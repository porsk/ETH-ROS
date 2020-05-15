#include <ros/ros.h>
#include "husky_stop_after_crash/HuskyStopAfterCrash.hpp"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "husky_stop_after_crash");
  ros::NodeHandle nodeHandle("~");

  husky_stop_after_crash::HuskyStopAfterCrash huskyStopAfterCrash(nodeHandle);

  ros::spin();
  return 0;
}
