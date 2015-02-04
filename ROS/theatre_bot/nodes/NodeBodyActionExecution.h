/*
 * NodeBodyActionExecution.h
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#ifndef NODEBODYACTIONEXECUTION_H_
#define NODEBODYACTIONEXECUTION_H_

#include <boost/shared_ptr.hpp>

#include "ros/ros.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../src/json/json/json.h"
#include "../src/Parsers/EmotionParser.h"

#include "../src/PlatformActionControllers/Body/BodyAction.h"
#include "../src/PlatformActionControllers/Body/KeeponBody.h"

#include "../src/Parameters/EmotionalParameters/EmotionMovementParameter.h"



class NodeBodyActionExecution {
public:
	NodeBodyActionExecution();
	virtual ~NodeBodyActionExecution();

	void callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void callbackNewEmotionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void setPlatform(std::string platform, ros::NodeHandle *node);
	void setPublisherActionSynch(ros::Publisher *pub_message);
private:
	EmotionParser emotion_parser;
	ros::Publisher *pub_action_synch;
	std::string action_name_move;
	std::string action_name_oscillate;

	//CallbackFunction
	BodyAction *body_action;

	//Json reader function
	bool parserJSON(std::string parameter, boost::shared_ptr<Position> *result, TypePosition * type_position_parameter);
	bool parserEmotionJSON(std::string parameter, std::vector<EmotionMovementParameter> *result);
	bool parserJSON(std::string parameter, Amplitude *result);
};

#endif /* NODEBODYACTIONEXECUTION_H_ */
