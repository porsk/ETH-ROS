#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  std::string topic_name = "/scan";
  int queue_size = 1;

  if (!nodeHandle_.getParam("husky/scan_subscriber_topic_name", topic_name)) {
    ROS_ERROR("No husky/scan_subscriber_topic_name parameter defined!");
  }

  if (!nodeHandle_.getParam("husky/scan_subscriber_queue_size", queue_size)) {
    ROS_ERROR("No husky/scan_subscriber_queue_size parameter defined!");
  }

  control_gain = 0.5;

  if (!nodeHandle_.getParam("husky/control_gain", control_gain)) {
      ROS_ERROR("No husky/control_gain parameter defined!");
  }

  subscriber_ = nodeHandle_.subscribe(topic_name, queue_size, &HuskyHighlevelController::scanCallback, this);
  cmd_publisher_ = nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  vis_publisher_ = nodeHandle_.advertise<visualization_msgs::Marker>("/visualization_marker", 1);

  // sleeping for a few seconds
  ros::Duration(10).sleep();
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

void HuskyHighlevelController::scanCallback(const sensor_msgs::LaserScan& msg)
{
  int size = msg.ranges.size();
  float min = msg.range_max;
  int minIndex = 0;

  for (int i = 0; i < size; i++) {
    if (msg.ranges.at(i) < min && msg.ranges.at(i) > msg.range_min) {
      min = msg.ranges.at(i);
      minIndex = i;
    }
  }

  float pillarAngle = msg.angle_min + (msg.angle_increment * minIndex);

  geometry_msgs::Twist cmd;

  // control robot to the pillar
  if (min > 1) {
    cmd.linear.x = 1; // speed
    cmd.angular.z = control_gain * (0 - pillarAngle); //angle
  } else {
    cmd.linear.x = 0; // speed
    cmd.angular.z = 0; //angle
  }

  cmd_publisher_.publish(cmd);

  // visualize pillar in Rviz
  visualization_msgs::Marker marker;
  marker.header.frame_id = "base_link";
  marker.header.stamp = ros::Time();

  marker.ns = "pillar";
  marker.id = 0;

  marker.type = visualization_msgs::Marker::CYLINDER;
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = (min + 1) * cos(pillarAngle);
  marker.pose.position.y = -(min) * sin(pillarAngle);
  marker.pose.position.z = 0;

  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 0.0;

  marker.scale.x = 1;
  marker.scale.y = 1;
  marker.scale.z = 1;

  marker.color.a = 1.0;
  marker.color.r = 0.0;
  marker.color.g = 0.0;
  marker.color.b = 1.0;

  vis_publisher_.publish(marker);

  ROS_INFO_STREAM("Minimum distance: " << min);
}

} /* namespace */
