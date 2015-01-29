/*
 * SimpleActionBodyNode.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: julian
 */


#include "ros/ros.h"
#include "tf/tf.h"
#include "std_msgs/Char.h"

#include "../triskar_small/Planning.h"

#include "theatrebot_action_modulation/SyncActionMessage.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"

using std::string;

void executeActionMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
void executeActionOscillate(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
void updateTriskarInformation(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg);
void actionFinishSync(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg);
void controlAngle(const std_msgs::Bool::ConstPtr& msg);

ros::Subscriber sub_platform;
ros::Publisher 	move_triskar;
ros::Publisher pub_control_triskar;
ros::Publisher pub_action_finish;
//To receive information when other action has finished
ros::Subscriber sub_action_finish;
//To know if should be controlled the angle
ros::Subscriber sub_control_angle;

theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed_move;
theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed_oscillate;
/*
 * This should be abstract in order to be used for different platform
 */
Planning *triskar;

//Informs if the next position should be get as a base
bool new_message_recieve;
bool action_is_executing;
bool control_angle;
bool is_emotional_action_oscillate = false;

string desire_platform = "triskar_small";

//Object to the robot

int main(int argc, char **argv){
	//Subscribe to the action action execution
	ros::init(argc, argv, "simple_action_move_body_node");
	ros::NodeHandle n("/action_modulation");
	ros::Subscriber sub_move = n.subscribe("simple_action_move_body_node", 5, executeActionMove);
	ros::Subscriber sub_oscillate = n.subscribe("simple_action_oscillate_body_node", 5, executeActionOscillate);
	if(desire_platform == "triskar_small"){
		triskar = new Planning();
		ROS_INFO("Move Action Triskar");
		sub_platform = 	n.subscribe("odometry_triskar", 5, updateTriskarInformation);
		move_triskar =  n.advertise<theatrebot_action_modulation::TriskarVelocity>("vel_triskar",1);
		pub_control_triskar = n.advertise<std_msgs::Char>("commands_triskar",1);
	}
	pub_action_finish = n.advertise<theatrebot_action_modulation::SyncActionMessage>(
				"sync_move_body",5);
	sub_action_finish = n.subscribe("action_execution_sync",5,actionFinishSync);
	sub_control_angle = n.subscribe("action_control_angle_roration",5,controlAngle);
	new_message_recieve = false;
	action_is_executing = false;
	control_angle = true;
	triskar->setControlAngle(control_angle);
	ROS_INFO("Ready to execute move body action");
	ros::spin();
	return 0;
}



void updateTriskarInformation(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg){
	if (action_is_executing) {
		theatrebot_action_modulation::TriskarVelocity message;
		if (new_message_recieve) {
			new_message_recieve = false;
			triskar->setInitialPosition(msg);
		}
		message = triskar->calculateVelocity(msg,information_to_performed_move, pub_action_finish);
		if(!control_angle)
			message.angular = triskar->calculateAngularVelocity(msg,information_to_performed_oscillate);
		if(triskar->hasArrived()){
			action_is_executing = false;
			new_message_recieve = false;
			control_angle = true;
			theatrebot_action_modulation::SyncActionMessage temp_message_finish;
			temp_message_finish.action_name.data = "move_body";
			temp_message_finish.type_message.data = "finish";
			temp_message_finish.action_success.data = true;
			pub_action_finish.publish(temp_message_finish);
			message.linear.x = 0.0;
			message.linear.y = 0.0;
			message.angular = 0.0;
			//ROS_INFO("the move action enter to finish");
		}
		ROS_INFO("POSITION [%f, %f, %f ]VELOCITY [%f ,%f, %f] control angle %d",msg->pose.position.x,msg->pose.position.y,msg->pose.orientation,
				message.linear.x, message.linear.y,message.angular, control_angle);
		move_triskar.publish(message);
	}
}

void executeActionOscillate(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg)
{
	ROS_INFO("Changing action oscillate body");
	//Copying the action information
	information_to_performed_oscillate.emotion_parameters.clear();
	information_to_performed_oscillate.action_name = msg->action_name;
	if(msg->action_type.data == "mandatory"){
		information_to_performed_oscillate.desire_position = msg->desire_position;
		information_to_performed_oscillate.trajectory_characteristic = msg->trajectory_characteristic;
		//TODO add finish condition because it just finish
		triskar->setIsEmotionalActionOScillate(false);
	} else if(msg->action_type.data == "emotional"){
		triskar->setIsEmotionalActionOScillate(true);
		information_to_performed_oscillate.desire_position = information_to_performed_move.desire_position;
		information_to_performed_oscillate.trajectory_characteristic = information_to_performed_move.trajectory_characteristic;
		//ROS_INFO("is emotional: %d", msg->emotion_parameters.size());
	}
	//Copying the actions
	for(int i=0;i<msg->emotion_parameters.size();i++){
		theatrebot_action_modulation::EmotionParametersMessage temp_message;
		temp_message.spacing = msg->emotion_parameters[i].spacing;
		temp_message.timing  = msg->emotion_parameters[i].timing;
		//ROS_INFO("parameters emotion oscillate [%f %f]",msg->emotion_parameters[i].timing, msg->emotion_parameters[i].spacing);
		information_to_performed_oscillate.emotion_parameters.push_back(temp_message);
	}
	information_to_performed_oscillate.action_is_principal = msg->action_is_principal;
	new_message_recieve = true;
	action_is_executing = true;
}


void executeActionMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg)
{
	ROS_INFO("Changing action move body");
	//Copying the action information
	information_to_performed_move.emotion_parameters.clear();
	if(msg->action_type.data == "mandatory"){
		information_to_performed_move.action_name = msg->action_name;
		information_to_performed_move.desire_position = msg->desire_position;
		information_to_performed_move.trajectory_characteristic = msg->trajectory_characteristic;
	}
	//Copying the actions
	for(int i=0;i<msg->emotion_parameters.size();i++){
		theatrebot_action_modulation::EmotionParametersMessage temp_message;
		temp_message.spacing = msg->emotion_parameters[i].spacing;
		temp_message.timing  = msg->emotion_parameters[i].timing;
		//ROS_INFO("parameters emotion Move [%f %f]",msg->emotion_parameters[i].timing, msg->emotion_parameters[i].spacing);
		information_to_performed_move.emotion_parameters.push_back(temp_message);
	}
	//ROS_INFO("pos %f %f %f",information_to_performed_move.desire_position.desire_position.position.x,
		//	information_to_performed_move.desire_position.desire_position.position.y,
		//	static_cast<float>(tf::getYaw(information_to_performed_move.desire_position.desire_position.orientation)));
	information_to_performed_move.action_is_principal = msg->action_is_principal;
	new_message_recieve = true;
	action_is_executing = true;
	ROS_INFO("Desire Position %f %f",information_to_performed_move.desire_position.desire_position.position.x,information_to_performed_move.desire_position.desire_position.position.y);
	//reset the distance in the planning
	triskar->reset();
}

void actionFinishSync(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg){
	if(msg->action_name.data=="not_do_anything"){
		if(msg->type_message.data =="stop"){
			action_is_executing = false;
			new_message_recieve = false;
			control_angle = true;
			std_msgs::Char t;
			t.data = 'S';
			pub_control_triskar.publish(t);
		}
	}else if (msg->type_message.data == "sync_emotion") {

	}
}

void controlAngle(const std_msgs::Bool::ConstPtr& msg){
	control_angle = msg->data;
	triskar->setControlAngle(control_angle);
}
