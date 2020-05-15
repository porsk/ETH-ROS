#include "husky_stop_after_crash/HuskyStopAfterCrash.hpp"

namespace husky_stop_after_crash {

HuskyStopAfterCrash::HuskyStopAfterCrash(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  subscriber_ = nodeHandle.subscribe("/imu/data", 5, &HuskyStopAfterCrash::imuCallback, this);
  client_ = nodeHandle.serviceClient<std_srvs::SetBool>("/stop_husky");  
}

HuskyStopAfterCrash::~HuskyStopAfterCrash() {
}

void HuskyStopAfterCrash::imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
  float acc_x = msg->linear_acceleration.x;
  float acc_y = msg->linear_acceleration.y;

  std_srvs::SetBool service;

  if (abs(acc_x) + abs(acc_y) > 10) {
    service.request.data = true;

    if (client_.call(service)) {
      ROS_INFO("Response: %s", service.response.message.c_str());
    } else {
      ROS_ERROR("Failed to stop robot.");
      return;
    }
  }
}

} /* namespace */
