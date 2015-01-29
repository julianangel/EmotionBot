/*
 * ActionAdditionBody.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: julian
 */
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "ros/ros.h"
#include "theatrebot_action_modulation/TriskarLinearVelocity.h"
#include "theatrebot_action_modulation/TriskarAngularVelocity.h"
#include "theatrebot_action_modulation/TriskarVelocity.h"

void updateAngularVelocity(const theatrebot_action_modulation::TriskarAngularVelocity::ConstPtr& msg);
void updateLinearVelocity(const theatrebot_action_modulation::TriskarLinearVelocity::ConstPtr& msg);

theatrebot_action_modulation::TriskarVelocity velocity;


int main(int argc, char **argv){
	ros::init(argc, argv, "simple_addition_body_node");
	ros::NodeHandle n("/action_modulation");
	ros::Subscriber sub_vel_l = n.subscribe("l_vel_triskar", 5, updateLinearVelocity);
	ros::Subscriber sub_vel_a = n.subscribe("a_vel_triskar", 5, updateAngularVelocity);
	ros::Publisher vel_pub = n.advertise<theatrebot_action_modulation::TriskarVelocity>("vel_triskar", 1);
	double begin = ros::Time::now().toSec();
	while(ros::ok()){
		 if(ros::Time::now().toSec()-begin>0.05
		                                &&(velocity.linear.x != 0
		                                ||velocity.linear.y != 0
		                                ||velocity.angular != 0)){
		                        ROS_INFO("angle to send %f %f %f",velocity.linear.x,velocity.linear.y,velocity.angular);
		                        vel_pub.publish(velocity);
		                        velocity.linear.x = 0;
		                        velocity.linear.y = 0;
		                        velocity.angular = 0;
			begin = ros::Time::now().toSec();
		}
		ros::spinOnce();
	}
	return 0;
}

void updateAngularVelocity(const theatrebot_action_modulation::TriskarAngularVelocity::ConstPtr& msg){
	velocity.angular = msg->angular;
}
void updateLinearVelocity(const theatrebot_action_modulation::TriskarLinearVelocity::ConstPtr& msg){
	velocity.linear.x = msg->linear.x;
	velocity.linear.y = msg->linear.y;
}



