/*
 * TestPositionNode.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: julian
 */


#include "ros/ros.h"
#include "tf/tf.h"
#include "geometry_msgs/Pose.h"
#include "theatrebot_action_modulation/OdometryTriskar.h"
#include "theatrebot_action_modulation/TriskarLinearVelocity.h"
#include "theatrebot_action_modulation/TriskarAngularVelocity.h"

theatrebot_action_modulation::OdometryTriskar message;
float time_of_simulation = 0.1; //given in milliseconds;
bool writing = false;
void updatePosition(const theatrebot_action_modulation::TriskarLinearVelocity::ConstPtr& msg);
void updateAngularPosition(const theatrebot_action_modulation::TriskarAngularVelocity::ConstPtr& msg);
int main(int argc, char **argv){

	ros::init(argc, argv, "position_triskar_test");
	ros::NodeHandle n;
	message.pose.position.x=1.0;
	message.pose.position.y=2.0;
	message.pose.orientation = 3.0;
	message.twist.linear.x = 4.0;
	message.twist.linear.y = 5.0;
	message.twist.angular = 6.0;
	ros::Subscriber sub_action = n.subscribe("l_velocity_triskar", 1000, updatePosition);
	ros::Subscriber sub_action2 = n.subscribe("a_velocity_triskar", 1000, updateAngularPosition);
	ros::Publisher pos_pub =
			n.advertise<theatrebot_action_modulation::OdometryTriskar>("odometry_triskar",1000);
	ROS_INFO("Ready to test modules");
	while(ros::ok()){
		if(!writing)
			pos_pub.publish(message);
		ROS_INFO("Pos [%f %f %f]",message.pose.position.x,
				message.pose.position.y,message.pose.orientation);
		for(int i = 0;i<10000000;i++);
		ros::spinOnce();
	}
	return 0;
}


void updateAngularPosition(const theatrebot_action_modulation::TriskarAngularVelocity::ConstPtr& msg){
	geometry_msgs::Pose temp_pose;
	temp_pose.orientation.x=msg->angular*time_of_simulation/80000;
	message.twist.angular = msg->angular;
}

void updatePosition(const theatrebot_action_modulation::TriskarLinearVelocity::ConstPtr& msg){
	writing = true;
	message.pose.position.x += msg->linear.x*time_of_simulation;
	message.pose.position.y += msg->linear.y*time_of_simulation;
	message.twist.linear.x = msg->linear.x;
	message.twist.linear.y =  msg->linear.y;
	writing = false;
}
