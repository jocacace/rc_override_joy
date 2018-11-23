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

	enum Buttons { X, A, B, Y, LB, RB };
	int _chan5, _chan6;

  //---params for axes/Buttons
  int _thurst_ax;
  int _roll_ax;
  int _pitch_ax;
  int _yaw_ax;
  int _chan5_low_btn;
  int _chan5_middle_btn;
  int _chan5_high_btn;
  int _chan6_low_btn;
  int _chan6_high_btn;
  //---

  float _thrust;
  float _roll;
  float _pitch;
  float _yaw;


};
