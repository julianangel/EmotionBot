/*
 * NodeActionModulation.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: julian
 */


#include "NodeActionModulation.h"


NodeActionModulation::NodeActionModulation(){

}
NodeActionModulation::~NodeActionModulation(){

}


void NodeActionModulation::stopActions(){
	std::vector<std::string> list = this->action_modulation_sub_system.actiosToStop();
	std::cout<<"actions to finish: ";
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
		//Here comes the messages to the action
		std::cout<<*it<<" "<<std::endl;
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.coming_to = *it;
		temp_message.coming_from = "";
		temp_message.message = "stop";
		temp_message.stop_action = true;
		this->pub_action_parameter->publish(temp_message);
	}
	std::cout<<std::endl;
}

void NodeActionModulation::callbackActionExecutionSynch(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	std::cout<<"Synch "<<msg->coming_from<<": "<<msg->message<<std::endl;
}

void NodeActionModulation::setActionParameter(ros::Publisher *pub_action_parameter){
	this->pub_action_parameter = pub_action_parameter;
}


void NodeActionModulation::setEmotionParameter(ros::Publisher *pub_emotion_parameter){
	this->pub_emotion_parameter = pub_emotion_parameter;
}
/*
 * when a change is done it should send a message to all the actions through the emotion channel
 */
void NodeActionModulation::callbackNewEmotion(const theatre_bot::EmotionMessage::ConstPtr& msg){
	std::string emotion = msg->emotion.data;
	float intensity = msg->intensity.data;
	ROS_INFO("Emotion %s, intensity %f", emotion.c_str(), intensity);
	action_modulation_sub_system.callBackNewEmotion(emotion,intensity);
	//stopActions
	this->stopActions();
	std::map<std::string,std::string> list_message_actions = action_modulation_sub_system.generateEmotionalParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		ROS_INFO("Sending emotions %s %s", it->first.c_str(), it->second.c_str());
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		this->pub_emotion_parameter->publish(temp_message);
	}
}

bool NodeActionModulation::callbackNewAction(theatre_bot::ActionService::Request &req, theatre_bot::ActionService::Response &res){
	std::string desire_action = req.action;
	ROS_INFO("the action:-%s-", desire_action.c_str());
	action_modulation_sub_system.callBackNewAction(desire_action);
	//stopActions
	this->stopActions();
	//Get the action messages
	std::map<std::string,std::string> list_message_actions = action_modulation_sub_system.generateParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the action channel
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		this->pub_action_parameter->publish(temp_message);
		ROS_INFO("Sending action parameters %s %s", it->first.c_str(), it->second.c_str());
	}
	list_message_actions = action_modulation_sub_system.generateEmotionalParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		ROS_INFO("Sending emotions %s %s", it->first.c_str(), it->second.c_str());
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		this->pub_emotion_parameter->publish(temp_message);
	}
	res.response = "done";
	return true;
}

void NodeActionModulation::loadInformation(){
	action_modulation_sub_system.setPathEmotion(path_name_emotion);
	action_modulation_sub_system.setPathCharacterPace(path_name_character);
	action_modulation_sub_system.loadInformation();
}

void NodeActionModulation::setPathEmotion(std::string path_emotion){
	this->path_name_emotion = path_emotion;
}

void NodeActionModulation::setPathCharacter(std::string path_character){
	this->path_name_character = path_character;
}

int main(int argc, char **argv){
	NodeActionModulation node;
	//Files with the specification
	//TODO this information should be given by parameters
	node.setPathEmotion("/home/julian/workspace/TheatreBot/emotion_profile");
	node.setPathCharacter("/home/julian/workspace/TheatreBot/character_description_emotion/character_one");
	node.loadInformation();
	//Init the node
	ros::init(argc, argv, "action_modulation_sub_system");
	ros::NodeHandle n;
	//Topic emotion
	ros::Subscriber sub = n.subscribe("change_emotion", 10, &NodeActionModulation::callbackNewEmotion, &node);
	//Topic synch
	ros::Subscriber sub_synch = n.subscribe("action_execution_synch", 10, &NodeActionModulation::callbackActionExecutionSynch, &node);
	//Service new emotion
	ros::ServiceServer service = n.advertiseService("change_action",&NodeActionModulation::callbackNewAction,&node);
	//Publishes the new action parameters
	ros::Publisher pub_action_parameter = n.advertise<theatre_bot::ActionExecutionMessage>("change_action_parameters", 10);
	node.setActionParameter(&pub_action_parameter);
	//Publishes the new emotion parameters
	ros::Publisher pub_emotion_parameter = n.advertise<theatre_bot::ActionExecutionMessage>("change_emotion_parameters", 10);
	node.setEmotionParameter(&pub_emotion_parameter);
	ros::spin();
	return 0;
}
