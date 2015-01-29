/*
 * JoyPadTriskar.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: julian
 */

#include "JoyPadTriskar.h"

JoyPadTriskar::JoyPadTriskar() {
	act_pub = nh_.advertise<theatrebot_action_modulation::TriskarVelocity>("/vel_triskar", 1);
	joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &JoyPadTriskar::joyCallback, this);
	pos_sub_ = nh_.subscribe<theatrebot_action_modulation::OdometryTriskar>("odometry_triskar", 10, &JoyPadTriskar::posTriskar, this);
	position_x = 0;
	position_y = 0;
	position_theata = 0;
	action_name = "walk";
}

JoyPadTriskar::~JoyPadTriskar() {
	// TODO Auto-generated destructor stub
}


void JoyPadTriskar::posTriskar(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& position){
	theatrebot_action_modulation::TriskarVelocity message;
	message.linear.x = position_x;
	message.linear.y = position_y;
	message.angular = position_theata;
	/*theatrebot_action_modulation::ActionDesireMessage action_desire;
	action_desire.action_name.data = action_name;
	action_desire.desire_position.type_parameter.data = "point_position";
	action_desire.desire_position.desire_position.position.x = position->pose.position.x+position_x;
	action_desire.desire_position.desire_position.position.y = position->pose.position.y+position_y;
	tf::Quaternion temp = tf::createQuaternionFromYaw(position_theata+position->pose.orientation);
	action_desire.desire_position.desire_position.orientation.x=temp.x();
	action_desire.desire_position.desire_position.orientation.z=temp.z();
	action_desire.desire_position.desire_position.orientation.y=temp.y();
	action_desire.desire_position.desire_position.orientation.w=temp.w();
	action_desire.trajectory_characteristic.type_parameter.data = "velocity_parameter";
	action_desire.trajectory_characteristic.trajectory_characteristic.linear.x=0;
	action_desire.trajectory_characteristic.trajectory_characteristic.linear.y=0;
	action_desire.trajectory_characteristic.trajectory_characteristic.angular.x=0;
	act_pub.publish(action_desire);*/
	act_pub.publish(message);
}

void JoyPadTriskar::joyCallback(const sensor_msgs::Joy::ConstPtr& joy){
	theatrebot_action_modulation::TriskarVelocity message;
	position_x = static_cast<float>(joy->axes[0]*-500);
	position_y = static_cast<float>(joy->axes[1]*500);
	position_theata = static_cast<float>(joy->axes[3]*2.5);
	ROS_INFO("%f %f %f",joy->axes[1]*4000,joy->axes[0]*400,position_theata);
	message.linear.x = position_x;
	message.linear.y = position_y;
	message.angular = position_theata;
	if(joy->buttons[0]==1){
		ROS_INFO("neutral");
	}else if(joy->buttons[1]==1){
		ROS_INFO("happy");
	}else if(joy->buttons[2]==1){
		ROS_INFO("angry");
	}else if(joy->buttons[3]==1){
		ROS_INFO("sad");
	}else if(joy->buttons[5]==1){
		ROS_INFO("content");
	}if(joy->buttons[7]==1){
		ROS_INFO("action_walk");
	}if(joy->buttons[6]==1){
		ROS_INFO("not_do_anything");
	}
	act_pub.publish(message);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_triskar");
  JoyPadTriskar teleop_triskar;

  ros::spin();
}
