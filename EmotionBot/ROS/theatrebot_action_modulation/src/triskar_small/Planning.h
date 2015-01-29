/*
 * Planning.h
 *
 *  Created on: Sep 25, 2014
 *      Author: julian
 */

#ifndef PLANNING_H_
#define PLANNING_H_

#include "ros/ros.h"
#include "tf/tf.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"
#include "theatrebot_action_modulation/SyncActionMessage.h"
#include "theatrebot_action_modulation/OdometryTriskar.h"
#include "theatrebot_action_modulation/TriskarVelocity.h"
#include "theatrebot_action_modulation/Pose32.h"

class Planning {
	#define ANGULAR_VELOCITY 2.5f
	#define LINEAL_VELOCITY 600.0f
	#define MAX_LINEAR_VELOCITY 910.0f
	#define MAX_ANGULAR_VELOCITY 	0.78539816339744830962f //rad/seg
public:
	Planning();
	virtual ~Planning();

	void setInitialPosition(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg);
	theatrebot_action_modulation::TriskarVelocity calculateVelocity(
			const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
			theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed,
			ros::Publisher pub_action_finish);
	float calculateAngularVelocity(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
			theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed);
	void reset();
	void setControlAngle(bool control_angle);
	bool hasArrived();
	void setIsEmotionalActionOScillate(bool is_emotional_action_oscillate);
private:
	float signum(float num);
	float fabs(float num);
	void calculateVelocityWithoutEmotion(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
			theatrebot_action_modulation::TriskarVelocity *message,
			float distance_x, float distance_y, float distance_theta,
			theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed);
	void calculateVelocityWithEmotion(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg
			,theatrebot_action_modulation::TriskarVelocity *message,
			float distance_x, float distance_y, float distance_theta, float temp_current_distance,
			float temp_angle_to_desire_position,
			theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed,
			ros::Publisher pub_action_finish);
	//it puts the angle between pi and -pi
	float correctAngle(float distance_theta);
	float temp_distance_traveled;
	//This is used for the emotional calculations
	float distance_travel;
	bool control_angle;
	bool has_arrived;
	float maximum_error_x;//in millimeters
	float maximum_error_y;//in millimeters
	float maximum_error_theta; //radians
	float reduce_velocity_distance; //in millimeters
	float reduce_velocity_angular_distance; //radians

	//Oscillate variables

	bool forward_direction;
	int current_position_emotion;
	float delta_time; //milli seconds
	bool is_emotional_action_oscillate;

	//Initial pose of the robot
	theatrebot_action_modulation::Pose32 initial_pose;

};

#endif /* PLANNING_H_ */
