#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  std::string topic_name;
  int queue_size;

  if (!nodeHandle_.getParam("husky/scan_subscriber_topic_name", topic_name)) {
    ROS_ERROR("No husky/scan_subscriber_topic_name parameter defined!");
  }

  if (!nodeHandle_.getParam("husky/scan_subscriber_queue_size", queue_size)) {
    ROS_ERROR("No husky/scan_subscriber_queue_size parameter defined!");
  }

  subscriber_ = nodeHandle_.subscribe(topic_name, queue_size, &HuskyHighlevelController::scanCallback, this);
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan& msg)
{
  int size = msg.ranges.size();
  float min = msg.range_max;

  for (int i = 0; i < size; i++) {
    if (msg.ranges.at(i) < min && msg.ranges.at(i) > msg.range_min) {
      min = msg.ranges.at(i);
    }
  }

  ROS_INFO_STREAM("Minimum distance: " << min);
}

} /* namespace */
