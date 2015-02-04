/*
 * BodyAction.h
 *
 *  Created on: Jan 30, 2015
 *      Author: julian
 */

#ifndef BODYACTION_H_
#define BODYACTION_H_

#include <boost/shared_ptr.hpp>
#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include "math.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../../Parameters/MovementParameters/TypePosition.h"
#include "../../Parameters/MovementParameters/Circle.h"
#include "../../Parameters/MovementParameters/Position.h"
#include "../../Parameters/MovementParameters/Point.h"
#include "../../Parameters/MovementParameters/Square.h"
#include "../../Parameters/MovementParameters/Landmark.h"
#include "../../Parameters/MovementParameters/Amplitude.h"
#include "../../Parameters/EmotionalParameters/EmotionMovementParameter.h"

class BodyAction {
public:
	BodyAction();
	virtual ~BodyAction();

	virtual void MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position) = 0;
	virtual void OscillateBodyAction(Amplitude parameter) = 0;
	virtual void stopMoveBodyAction() = 0;
	virtual void stopOscillateBodyAction() = 0;
	virtual void synchEmotionMove() = 0;
	virtual void synchEmotionOscillate() = 0;
	virtual void setPublisherAction(ros::NodeHandle *node) = 0;
	virtual void initSubscriberAction(ros::NodeHandle *node) = 0;

	void setPublisherActionSynch(ros::Publisher *pub_action_synch);
	void setActionMoveName(std::string name);
	void setActionOscillateName(std::string name);
protected:
	std::string action_move_name;
	std::string action_oscillation_name;
	float delta_time;

	ros::Publisher *pub_action_synch;
	//Move
	float x;
	float y;
	float z;
	float x_error;
	float y_error;
	float z_error;
	float desire_x;
	float desire_y;
	float desire_z;
	float yaw;
	float pitch;
	float roll;
	float yaw_error;
	float pitch_error;
	float roll_error;
	float desire_yaw;
	float desire_pitch;
	float desire_roll;
	bool is_moving;
	float velocity_rotate;//It is the same for oscillation
	//Oscillate
	float desire_angle_to_oscillate_yaw;
	float desire_angle_to_oscillate_pitch;
	float desire_angle_to_oscillate_roll;
	bool forward_direction_yaw;
	bool forward_direction_pitch;
	bool forward_direction_roll;
	bool is_oscillating;
	//Emotion variable
	bool is_moving_emotional;
	bool is_oscillating_emotional;
	//Emotional parameters
	float velocity_emotional_rotate;
	bool repeat_move;
	bool repeat_oscillation;
	int pos_move_x;
	int pos_move_y;
	int pos_move_z;
	int pos_oscillate_x;
	int pos_oscillate_y;
	int pos_oscillate_z;
	std::vector<EmotionMovementParameter> move_x;
	std::vector<EmotionMovementParameter> move_y;
	std::vector<EmotionMovementParameter> move_z;
	std::vector<EmotionMovementParameter> oscillate_x;
	std::vector<EmotionMovementParameter> oscillate_y;
	std::vector<EmotionMovementParameter> oscillate_z;
	float updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	void verifyAngle(float *number);
};

#endif /* BODYACTION_H_ */
