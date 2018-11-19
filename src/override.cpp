#include "override.h"

using namespace std;

rc_override::rc_override() {
  _rc_pub = _nh.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 0);
  _joy_sub = _nh.subscribe("/joy", 0, &rc_override::joy_cb, this);

  _a0 = _a1 = _b0 = _b1 = 0.0;
}

void rc_override::joy_cb( sensor_msgs::Joy data ) {
  _a0 = data.axes[0];
  _a1 = data.axes[1];
  _b0 = data.axes[2];
  _b1 = data.axes[3];
}

void rc_override::run() {
  boost::thread override_t( &rc_override::override, this);
  ros::spin();
}


void rc_override::override() {

  mavros_msgs::OverrideRCIn rc;

  ros::Rate r(10);
  while(ros::ok()) {

    rc.channels[0] = ( _b0 >= 0.0 ) ? (_b0*700) + 1500 : (1500 + (_b0*700) );
    rc.channels[1] = ( _b1 <= 0.0 ) ? (_b1*700) + 1500 : (1500 + (_b1*700) );
    rc.channels[2] = ( _a1 > 0.0 ) ? (_a1*700) + 1500 : 800;
    rc.channels[3] = ( _a0 <= 0.0 ) ? (_a0*700) + 1500 : (1500 + (_a0*700) );

    _rc_pub.publish( rc ) ;
    r.sleep();
  }
}

int main( int argc, char** argv ) {

  ros::init( argc, argv, "rc_override");

  rc_override over;
  over.run();

  return 0;
}
