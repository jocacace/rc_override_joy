# rc_override_joy

This package maps standard joypad data recevied on a *sensor_msgs::Joy* topic in a *mavros_msgs::OverrideRCIn* message, in order to control a real or simulated UAV running mavros overriding the RC data as input of the autopilot.

### Input

  * __Joystick data__: on */joy* topic  

### Output

  * __rc_data__: on */mavros/rc/override* topic

## Configuration

To configure your own joypad you can use a set of ROS parameters, as specified in the example launch file in *rc_override_joy/launch/rc_override.launch*. In this file you can specify the axes and the buttons to use to override the RC channels:

  * *thurst_ax*: specifies the __axis__ to control the throttle
  * *roll_ax*: specifies the __axis__ to control the roll
  * *pitch_ax*: specifies the __axis__ to control the pitch
  * *yaw_ax*: specifies the __axis__ to control the yaw
  * *chan5_low_btn*: specifies the __button__ to set at low value the channel 5
  * *chan5_middle_btn*: specifies the __button__ to set at middle value the channel 5
  * *chan5_high_btn*: specifies the __button__ to set at high value the channel 5
  * *chan6_low_btn*: specifies the __button__ to set at low value the channel 6
  * *chan6_high_btn*: specifies the __button__ to set at high value the channel 6

To set the desired parameter values, you can check how is configured your joypad. To do this, you can *echo* the */joy* topic, where the joypad data are streamed:

    $ roslaunch r_override_joy rc_override.roslaunch
    $ rostopic echo /joy
Now you can move the buttons and the sticks of your joypad configration, save the *id* of the axes and buttons field.  

    std_msgs/Header header
      uint32 seq
      time stamp
      string frame_id
    float32[] axes
    int32[] buttons

## Running the node
To start the rc_override node launche the properly configured launch file:

    $ roslaunch r_override_joy rc_override.roslaunch
