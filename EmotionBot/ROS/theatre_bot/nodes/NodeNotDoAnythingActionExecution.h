/*
 * NodeNotDoAnythingActionExecution.h
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#ifndef NODENOTDOANYTHINGACTIONEXECUTION_H_
#define NODENOTDOANYTHINGACTIONEXECUTION_H_

#include "ros/ros.h"
#include "ros/time.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../src/json/json/json.h"

class NodeNotDoAnythingActionExecution {
public:
	NodeNotDoAnythingActionExecution();
	virtual ~NodeNotDoAnythingActionExecution();

	void callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);

	void executeTime(float time);
	void setPublisherActionSynch(ros::Publisher *pub_message);
private:
	ros::Publisher *pub_action_synch;
	std::string action_name;
};

#endif /* NODENOTDOANYTHINGACTIONEXECUTION_H_ */
