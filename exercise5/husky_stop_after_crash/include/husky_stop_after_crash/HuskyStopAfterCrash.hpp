#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_srvs/SetBool.h>

namespace husky_stop_after_crash {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyStopAfterCrash {
public:
	/*!
	 * Constructor.
	 */
	HuskyStopAfterCrash(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyStopAfterCrash();

private:
	ros::NodeHandle& nodeHandle_;
	ros::Subscriber subscriber_;
	ros::ServiceClient client_;

	void imuCallback(const sensor_msgs::Imu::ConstPtr& msg);
};

} /* namespace */
