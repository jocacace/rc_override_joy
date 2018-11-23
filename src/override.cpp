#include "override.h"

using namespace std;

//---Get parameters
void load_param( double & p, double def, string name ) {
	ros::NodeHandle n_param("~");
	if( !n_param.getParam( name, p))
		p = def;
	cout << name << ": " << "\t" << p << endl;
}

void load_param( int & p, int def, string name ) {
	ros::NodeHandle n_param("~");
	if( !n_param.getParam( name, p))
		p = def;
	cout << name << ": " << "\t" << p << endl;
}

void load_param( bool & p, bool def, string name ) {
	ros::NodeHandle n_param("~");
	if( !n_param.getParam( name, p))
		p = def;
	cout << name << ": " << "\t" << p << endl;
}

void load_param( string & p, string def, string name ) {
	ros::NodeHandle n_param("~");
	if( !n_param.getParam( name, p))
		p = def;
	cout << name << ": " << "\t" << p << endl;
}
//---


rc_override::rc_override() {
  _rc_pub = _nh.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 0);
  _joy_sub = _nh.subscribe("/joy", 0, &rc_override::joy_cb, this);

  load_param( _thurst_ax, 1, "thrust_ax" );
  load_param( _yaw_ax,    0, "yaw_ax" );
  load_param( _roll_ax,   2, "roll_ax" );
  load_param( _pitch_ax,  3, "pitch_ax" );

  load_param( _chan5_low_btn,  		0, "chan5_low_btn" );
  load_param( _chan5_middle_btn,  1, "chan5_middle_btn" );
  load_param( _chan5_high_btn,  	2, "chan5_high_btn" );

  load_param( _chan6_low_btn,  	4, "chan6_low_btn" );
  load_param( _chan6_high_btn,  6, "chan6_high_btn" );

	_thrust = _roll = _pitch = _yaw = 0.0;
	_chan5 = 1500;
	_chan6 = 1000;
}

void rc_override::joy_cb( sensor_msgs::Joy data ) {

	_yaw = data.axes[_yaw_ax];
	_thrust = data.axes[_thurst_ax];
  _roll = data.axes[_roll_ax];
  _pitch = data.axes[_pitch_ax];

	if (data.buttons[_chan5_low_btn]){
		_chan5 = 1000;
	}
	if (data.buttons[_chan5_middle_btn]){
		_chan5 = 1500;
	}
	if (data.buttons[_chan5_high_btn]){
		_chan5 = 2000;
	}
	if (data.buttons[_chan6_low_btn]){
		_chan6 = 1000;
	}
	if (data.buttons[_chan6_high_btn]){
		_chan6 = 2000;
	}
}

void rc_override::run() {
  boost::thread override_t( &rc_override::override, this);
  ros::spin();
}


void rc_override::override() {

  mavros_msgs::OverrideRCIn rc;

  ros::Rate r(20);
  while(ros::ok()) {

    rc.channels[0] = ( _roll > 0.0 ) ? (_roll*500) + 1500 : (1500 + (_roll*500) );
    rc.channels[1] = ( _pitch <= 0.0 ) ? (_pitch*500) + 1500 : (1500 + (_pitch*500) );
    rc.channels[2] = ( _thrust > 0.0 ) ? (_thrust*500) + 1500 : (1500 + (_thrust*500) );
    rc.channels[3] = ( _yaw <= 0.0 ) ? (_yaw*500) + 1500 : (1500 + (_yaw*500) );
		rc.channels[4] = _chan5;
		rc.channels[5] = _chan6;

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
