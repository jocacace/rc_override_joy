#include "ros/ros.h"
#include "boost/thread.hpp"
#include "sensor_msgs/Joy.h"
#include "mavros_msgs/OverrideRCIn.h"

class rc_override {

public:
  rc_override();

  void joy_cb( sensor_msgs::Joy joy );
  void run();
  void override();

private:
  ros::NodeHandle _nh;
  ros::Publisher _rc_pub;
  ros::Subscriber _joy_sub;

  float _a0, _a1;
  float _b0, _b1;
	enum Buttons { X, A, B, Y, LB, RB };
	int _chan5, _chan6;

};
