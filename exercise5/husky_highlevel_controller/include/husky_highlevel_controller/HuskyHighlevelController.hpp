#pragma once

#include <ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <std_srvs/SetBool.h>
#include <string>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	ros::Publisher cmd_publisher_;
	ros::Publisher vis_publisher_;
	ros::ServiceServer service_;

	float control_gain;
	bool stop;

	void scanCallback(const sensor_msgs::LaserScan& msg);
	bool stopCallback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response);
};

} /* namespace */
