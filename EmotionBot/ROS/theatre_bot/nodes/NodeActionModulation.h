/*
 * NodeActionModulation.h
 *
 *  Created on: Dec 28, 2014
 *      Author: julian
 */

#ifndef NODEACTIONMODULATION_H_
#define NODEACTIONMODULATION_H_

#include <string>
#include <vector>

#include "ros/ros.h"

#include "theatre_bot/EmotionMessage.h"
#include "theatre_bot/ActionService.h"
#include "theatre_bot/ActionExecutionMessage.h"

#include "../src/ActionModulation/ActionModulationSubSystem.h"
#include "../src/ActionModulation/ActionModulationSubSystem.h"

class NodeActionModulation {
public:
	NodeActionModulation();
	virtual ~NodeActionModulation();
	void callbackNewEmotion(const theatre_bot::EmotionMessage::ConstPtr& msg);
	bool callbackNewAction(theatre_bot::ActionService::Request &req, theatre_bot::ActionService::Response &res);
	void callbackActionExecutionSynch(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void loadInformation();
	void setPathEmotion(std::string path_emotion);
	void setPathCharacter(std::string path_character);

	void setActionParameter(ros::Publisher *pub_action_parameter);
	void setEmotionParameter(ros::Publisher *pub_emotion_parameter);
private:
	void stopActions();
	ActionModulationSubSystem action_modulation_sub_system;

	std::string path_name_emotion;
	std::string path_name_character;

	ros::Publisher *pub_action_parameter;
	ros::Publisher *pub_emotion_parameter;
};


#endif /* NODEACTIONMODULATION_H_ */
