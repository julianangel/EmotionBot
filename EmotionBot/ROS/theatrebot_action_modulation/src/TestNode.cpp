/*
 * TestNode.cpp
 *
 *  Created on: May 29, 2014
 *      Author: julian
 */




#include "ros/ros.h"
#include "tf/tf.h"
#include <cstdio>
#include <iostream>
#include "theatrebot_action_modulation/ActionDesireMessage.h"
#include "theatrebot_action_modulation/EmotionModulationMessage.h"

using std::cin;
using std::string;

int main(int argc, char **argv){
	ros::init(argc, argv, "action_modulation_test");
	ros::NodeHandle n("/action_modulation");
	char c;
	theatrebot_action_modulation::ActionDesireMessage action_test;
	//Desire action
	action_test.action_name.data = "walk_and_speak";
	//action_test.action_name.data = "walk";http://www.cplusplus.com/forum/general/53781/
	//Position information
	action_test.desire_position.type_parameter.data = "point_position";
	action_test.desire_position.desire_position.position.x = 4000.0;
	action_test.desire_position.desire_position.position.y = 4000.0;
	action_test.desire_position.desire_position.orientation =
			tf::createQuaternionMsgFromYaw(0.0);
	//Trajectory information
	action_test.trajectory_characteristic.type_parameter.data =
			"velocity_parameter";
	action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
			500.0;
	action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
			500.0;
	action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
			0.0;
	ros::Publisher action_emotion_pub = n.advertise<std_msgs::String>("new_emotion",1000);
	std_msgs::String temp_emotion;
	ros::Publisher actions_pub = n.advertise<
			theatrebot_action_modulation::ActionDesireMessage>("new_action",
			1000);
	ROS_INFO("Ready to test modules");
	ros::Rate loop_rate(10);
	while (ros::ok()) {
		//loop_rate.sleep();
		cin >> c;
		if (c == 'a') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 0.0;
			action_test.desire_position.desire_position.position.y = 0.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(0.0);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					600.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					600.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			temp_emotion.data = "neutral";
			action_emotion_pub.publish(temp_emotion);
			actions_pub.publish(action_test);
			ROS_INFO("Send info");
		} else if (c == 'b') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 0.0;
			action_test.desire_position.desire_position.position.y = 0.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(-M_PI/2);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			actions_pub.publish(action_test);
			temp_emotion.data = "neutral";
			action_emotion_pub.publish(temp_emotion);
			ROS_INFO("Send info");
		} else if (c == 'c') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 0.0;
			action_test.desire_position.desire_position.position.y = 0.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(M_PI/2);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			actions_pub.publish(action_test);
			temp_emotion.data = "neutral";
			action_emotion_pub.publish(temp_emotion);
			ROS_INFO("Send info");
		} else if (c == 'd') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 0.0;
			action_test.desire_position.desire_position.position.y = 0.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(M_PI);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			actions_pub.publish(action_test);
			temp_emotion.data = "neutral";
			action_emotion_pub.publish(temp_emotion);
			ROS_INFO("Send info");
		} else if (c == 'e') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 0.0;
			action_test.desire_position.desire_position.position.y = 600.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(0.0);
			ROS_INFO("%f %f %f %f",
					action_test.desire_position.desire_position.orientation.x,
					action_test.desire_position.desire_position.orientation.y,
					action_test.desire_position.desire_position.orientation.z,
					action_test.desire_position.desire_position.orientation.w);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			actions_pub.publish(action_test);
			ROS_INFO("Send info");
		} else if (c == 'f') {
			action_test.action_name.data = "walk_and_speak";
			action_test.desire_position.desire_position.position.x = 600.0;
			action_test.desire_position.desire_position.position.y = 0.0;
			action_test.desire_position.desire_position.orientation =
					tf::createQuaternionMsgFromYaw(0.0);
			ROS_INFO("%f %f %f %f",
					action_test.desire_position.desire_position.orientation.x,
					action_test.desire_position.desire_position.orientation.y,
					action_test.desire_position.desire_position.orientation.z,
					action_test.desire_position.desire_position.orientation.w);
			//Trajectory information
			action_test.trajectory_characteristic.type_parameter.data =
					"velocity_parameter";
			action_test.trajectory_characteristic.trajectory_characteristic.linear.x =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.linear.y =
					0.0;
			action_test.trajectory_characteristic.trajectory_characteristic.angular.x =
					0.0;
			actions_pub.publish(action_test);
			ROS_INFO("Send info");
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
