/*
 * JoyPadTriskar.h
 *
 *  Created on: Oct 3, 2014
 *      Author: julian
 */

#ifndef JOYPADTRISKAR_H_
#define JOYPADTRISKAR_H_
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "tf/tf.h"
#include "theatrebot_action_modulation/ActionDesireMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"
#include "theatrebot_action_modulation/OdometryTriskar.h"
#include "theatrebot_action_modulation/TriskarVelocity.h"
class JoyPadTriskar {
public:
	JoyPadTriskar();
	virtual ~JoyPadTriskar();
private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void posTriskar(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& position);
	ros::NodeHandle nh_;
	ros::Publisher act_pub;
	ros::Publisher emo_pub;
	ros::Subscriber joy_sub_;
	ros::Subscriber pos_sub_;
	std::string action_name;
	float position_x;
	float position_y;
	float position_theata;
};

#endif /* JOYPADTRISKAR_H_ */
