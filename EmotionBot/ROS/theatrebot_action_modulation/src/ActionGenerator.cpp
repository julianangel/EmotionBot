/*
 * ActionGenerator.cpp
 *
 *  Created on: May 29, 2014
 *      Author: julian
 */


#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "ros/ros.h"
#include "instances/platform_profiles/PlatformTest1.h"
#include "theatrebot_action_modulation/SyncActionMessage.h"
#include "theatrebot_action_modulation/ActionExecutionMessage.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"

using std::string;
using std::vector;

void executeActions(const theatrebot_action_modulation::ActionExecutionMessage::ConstPtr& msg);
//TODO implement file parameters
void loadParameters(string file);
//TODO implement the platform information from file and change the platform description
void loadPlatformAction(string file);
//void generateExecuteGeneratePublisher(ros::NodeHandle n);
/*
 * This function is used to sync all the actions, the other actions should communicate when
 * they finish the execution of the action.
 * TODO which information should be share?
 */
void synchInformation(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg);


string desire_platform = "triskar_small";
map <string,string> simple_actions_platform;
//change to action lib, because i should stop this if... i have to think about this
ros::Publisher actions_pub_speak;
ros::Publisher actions_pub_move_body;
ros::Publisher actions_pub_move_shoulder;
ros::Publisher actions_pub_move_torso;
ros::Publisher actions_pub_oscillate_shoulder;
ros::Publisher actions_pub_oscillate_body;
ros::Publisher actions_pub_oscillate_torso;
ros::Subscriber actions_finish_sub_speak;
ros::Subscriber actions_finish_sub_move_body;
ros::Subscriber actions_finish_sub_move_shoulder;

//To know if should be controlled the angle
ros::Publisher pub_control_angle;
ros::Publisher pub_actions_execution_sync;

int main(int argc, char **argv){
	// Set up ROS.
	PlatformTest1 *platform_description = new PlatformTest1;
	simple_actions_platform = platform_description->getPlatformAction(desire_platform);
	ros::init(argc, argv, "action_modulation_generator");
	ros::NodeHandle n("/action_modulation");
	ros::Subscriber sub = n.subscribe("simple_actions_to_execute", 1000, executeActions);
	//Load  information
	if(n.getParam("/action_modulation/platform",desire_platform)){
		simple_actions_platform = platform_description->getPlatformAction(desire_platform);
	}
	//Load from file
	actions_pub_speak =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_speak_node",1000);
	actions_pub_move_body =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_move_body_node",1000);
	actions_pub_move_torso =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_move_torso_node",1000);
	actions_pub_move_shoulder =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_move_shoulder_node",1000);
	actions_pub_oscillate_shoulder =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_oscillate_shoulder_node",1000);
	actions_pub_oscillate_body =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_oscillate_body_node",1000);
	actions_pub_oscillate_torso =  n.advertise<theatrebot_action_modulation::ActionExecutionActionDescriptionMessage>("simple_action_oscillate_torso_node",1000);
	pub_actions_execution_sync = n.advertise<theatrebot_action_modulation::SyncActionMessage>("action_execution_sync",1000);
	pub_control_angle = n.advertise<std_msgs::Bool>("action_control_angle_roration",1000);
	actions_finish_sub_speak = n.subscribe("sync_speak",1000,synchInformation);
	actions_finish_sub_move_body = n.subscribe("sync_move_body",1000,synchInformation);
	actions_finish_sub_move_shoulder = n.subscribe("sync_move_shoulder",1000,synchInformation);
	//Subscriber to each action that finish
	ROS_INFO("Ready to execute actions");
	ros::spin();

	return 0;
}


void synchInformation(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg){
	//Get the action
	//TODO do something more intelligent with this
	//Inform the others actions
	pub_actions_execution_sync.publish(msg);
}

void executeActions(const theatrebot_action_modulation::ActionExecutionMessage::ConstPtr& msg)
{
	ROS_INFO("----New action----");
	//Variable to know if the move body should have control the angle of the platform
	std_msgs::Bool temp_oscillate_body;
	temp_oscillate_body.data = true;
	string temp_action_name_platform;
	//Look if all the actions could be performed by the platform
	for(int i=0;i<msg->actions_message.size();i++){
		temp_action_name_platform
			= simple_actions_platform[msg->actions_message[i].action_name.data];
		ROS_INFO("I heard: [%s]", msg->actions_message[i].action_name.data.c_str());
		//If the action is the list of this platform
		if(temp_action_name_platform!=""){
			//Send the messages to the correspond node
			ROS_INFO("The action is %s", temp_action_name_platform.c_str());
			if(temp_action_name_platform=="speak"){
				actions_pub_speak.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="move_body"){
				actions_pub_move_body.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="move_torso"){
				ROS_INFO("is ready to send to move_torso");
				actions_pub_move_torso.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="move_shoulder"){
				actions_pub_move_shoulder.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="oscillate_torso"){
				actions_pub_oscillate_torso.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="oscillate_body"){
				temp_oscillate_body.data = false;
				actions_pub_oscillate_body.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="oscillate_shoulder"){
				actions_pub_oscillate_shoulder.publish(msg->actions_message[i]);
			}if(temp_action_name_platform=="not_do_anything"){
				theatrebot_action_modulation::SyncActionMessage temp_message;
				temp_message.action_name.data = "not_do_anything";
				temp_message.type_message.data = "stop";
				pub_actions_execution_sync.publish(temp_message);
			}
		}
	}
	pub_control_angle.publish(temp_oscillate_body);
}
//TODO implement file parameters
void loadParameters(string file){

}

//TODO implement the platform information from file
void loadPlatformAction(string file){
}
