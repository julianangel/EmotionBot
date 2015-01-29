/*
 * ActionModulation.cpp
 *
 *  Created on: May 26, 2014
 *      Author: julian
 */

#include "ros/ros.h"
#include "tf/tf.h"
#include "theatrebot_action_modulation/ActionDesireMessage.h"
#include "theatrebot_action_modulation/ActionExecutionMessage.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"
#include <std_msgs/String.h>
#include <string>
#include <list>
#include <typeinfo>
#include <boost/shared_ptr.hpp>
#include "DecryptAction.h"

using std::string;
using std::list;
using boost::shared_ptr;

DecryptAction *decrypt_action;
list<shared_ptr<SimpleActionExecution> > simple_actions;
shared_ptr<ParameterPosition> parameter_position;
shared_ptr<ParameterTranslation> parameter_translation;
theatrebot_action_modulation::ActionDesireMessage action_desire;
string current_action;
string current_emotion;
//This variable is used to know if it should be done the addition of the emotions
bool information_loaded;
ros::Publisher actions_pub;

//Callback functions
void modulateActionNewEmotion(const std_msgs::String::ConstPtr& msg);
void modulateActionNewAction(
		const theatrebot_action_modulation::ActionDesireMessage::ConstPtr& info);
theatrebot_action_modulation::ActionExecutionMessage generateMessageOfActions();
void generateActions();

int main(int argc, char **argv){

	ros::init(argc, argv, "action_modulation_decrypt");
	ros::NodeHandle n("/action_modulation");
	std::string param_emotion, param_platform;
	if(!n.hasParam("directory_emotions")&&!n.hasParam("platform_profile")){
		ROS_INFO("it is necessary the information of the directory where the emotion information");
	}else{
		// Set up ROS.std_msgs::String::ConstPtr& msg

		n.getParam("directory_emotions", param_emotion);
		n.getParam("actions_file", param_platform);
		current_action = "not_do_anything";
		current_emotion = "neutral";

		decrypt_action = new DecryptAction;
		//If there was not possible to load the emotions
		information_loaded = decrypt_action->loadInformation(param_emotion,param_platform);
		decrypt_action->setEmotionsProfilesLoad(information_loaded);
		if(!information_loaded){
			ROS_INFO("it was impossible to load the emotions, system will work without emotions: ");
		}

		ros::Subscriber sub_action = n.subscribe("new_action", 1000, modulateActionNewAction);
		ros::Subscriber sub_emotion = n.subscribe("new_emotion", 1000, modulateActionNewEmotion);
		actions_pub = n.advertise<theatrebot_action_modulation::ActionExecutionMessage>("simple_actions_to_execute",1000);
		ROS_INFO("Ready to modulate actions");
		ros::spin();
	}
	return 0;
}

void modulateActionNewEmotion(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	current_emotion = msg->data;
	generateActions();
}

theatrebot_action_modulation::ActionExecutionMessage generateMessageOfActions(){
	theatrebot_action_modulation::ActionExecutionMessage temp_message;
	//moves over the whole list of actions
	for(list<shared_ptr<SimpleActionExecution> >::iterator it = simple_actions.begin();
			it != simple_actions.end();it++){
		theatrebot_action_modulation::ActionExecutionActionDescriptionMessage temp_action_description;
		if(typeid((*it)).name()==typeid(SpeakExecution).name()){
			//TODO do something
		}else if(typeid((*it)).name()==typeid(NotDoAnythingExecution).name()){
			temp_action_description=(*it)->getMessage();
		}
		else{
			//TODO implement for other possibilities
			temp_action_description=(*it)->getMessage();
		}
		//Addition of the emotions
		temp_message.actions_message.push_back(temp_action_description);
		ROS_INFO("ACTION %s",temp_action_description.action_name.data.c_str());
	}
	ROS_INFO("the message: %d",temp_message.actions_message.size());
	return temp_message;
}

void modulateActionNewAction(
		const theatrebot_action_modulation::ActionDesireMessage::ConstPtr& info){
	ROS_INFO("I heard: [%s]", info->action_name.data.c_str());
	//Delete last list
	simple_actions.clear();
	//Get the action name
	current_action = info->action_name.data;
	action_desire.action_name = info->action_name;
	action_desire.desire_position = info->desire_position;
	action_desire.trajectory_characteristic = info->trajectory_characteristic;
	generateActions();
}

void generateActions(){
	theatrebot_action_modulation::ActionExecutionMessage msg_actions;
	//If the action is different of not_do_anything
	if(current_action!="not_do_anything"){
			//Generate new parameters
			if(action_desire.desire_position.type_parameter.data=="point_position"){
				shared_ptr<PointPositionParameter> temp_position_parameter(new PointPositionParameter);
				tf::Quaternion temp_quaternion;
				tf::quaternionMsgToTF(action_desire.desire_position.desire_position.orientation,temp_quaternion);
				temp_position_parameter->setPointPosition(
						action_desire.desire_position.desire_position.position.x,
						action_desire.desire_position.desire_position.position.y,
						tf::getYaw(temp_quaternion));
				parameter_position = temp_position_parameter;
			}else if(action_desire.desire_position.type_parameter.data=="area_position"){
				ROS_INFO("Not implemented yet");
			}else if(action_desire.desire_position.type_parameter.data=="landmark_position"){
				ROS_INFO("Not implemented yet");
			}
			//Generate constrains
			if(action_desire.trajectory_characteristic.type_parameter.data=="velocity_parameter"){
				shared_ptr<ParameterVelocity> temp_parameter_translation(new ParameterVelocity);
				temp_parameter_translation->setVelocity(
						action_desire.trajectory_characteristic.trajectory_characteristic.linear.x,
						action_desire.trajectory_characteristic.trajectory_characteristic.linear.y,
						action_desire.trajectory_characteristic.trajectory_characteristic.angular.x);
				parameter_translation = temp_parameter_translation;
				ROS_INFO("Parameter Velocity");
			}else if(action_desire.trajectory_characteristic.type_parameter.data=="time_parameter"){
				ROS_INFO("Not implemented yet");
			}else if(action_desire.trajectory_characteristic.type_parameter.data=="acceleration_parameter"){
				ROS_INFO("Not implemented yet");
			}
			//Generate list simple actions
			ROS_INFO("Action to modulate:: %s",current_action.c_str());
			if(current_action == "speak"){
				string temp_speak = action_desire.phrase_to_say.data;
				simple_actions = decrypt_action->analyzeActions(current_action,
						current_emotion,temp_speak);
			}else if(current_action == "walk_and_speak"){
				string temp_speak = action_desire.phrase_to_say.data;
				simple_actions = decrypt_action->analyzeActions(current_action,current_emotion,
						parameter_position,parameter_translation,temp_speak);
			}else{
				ROS_INFO("Ready to execute");
				simple_actions = decrypt_action->analyzeActions(current_action,current_emotion,
								parameter_position,parameter_translation);
			}
		}else{
			simple_actions = decrypt_action->analyzeActions(current_action);
		}
		//Generate message
		msg_actions = generateMessageOfActions();
		for(int i=0; i< msg_actions.actions_message.size();i++){
			ROS_INFO("The actions are: [%s]", msg_actions.actions_message[i].action_name.data.c_str());
		}
		//Publish message
		actions_pub.publish(msg_actions);
}


