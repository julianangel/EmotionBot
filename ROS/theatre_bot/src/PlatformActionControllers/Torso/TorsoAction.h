/*
 * TorsoAction.h
 *
 *  Created on: Jan 26, 2015
 *      Author: julian
 */

#ifndef TORSOACTION_H_
#define TORSOACTION_H_


#include "ros/ros.h"
#include "math.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../../Parameters/MovementParameters/Amplitude.h"

class TorsoAction {
public:
	TorsoAction();
	virtual ~TorsoAction();
	virtual void MoveTorsoAction(Amplitude parameter) = 0;
	virtual void OscillateTorsoAction(Amplitude parameter) = 0;
	virtual void setPublisherAction(ros::NodeHandle *node) = 0;
	virtual void initSubscriberAction(ros::NodeHandle *node) = 0;
	virtual void stopMoveTorsoAction() = 0;
	virtual void stopOscillateTorsoAction() = 0;
	float updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle);
	float updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	void setPublisherActionSynch(ros::Publisher *pub_action_synch);
	void setActionMoveName(std::string action_name);
	void setActionOscillateName(std::string action_name);
protected:
	std::string action_name_move;
	std::string action_name_oscillate;
	ros::Publisher *pub_action_synch;
	//These variables are to decide the angles to oscillate
	float desire_angle_to_oscillate; //pitch
	float desire_angle_to_oscillate_y; //roll
	float desire_angle_to_oscillate_z;
	//front and back
	float desire_angle_to_move;
	//left to right
	float desire_angle_to_side;
	float desire_angle_to_z;
	bool is_oscillating; //it determines if the robot has to oscillate
	float delta_time; //milli seconds
	bool forward_direction_x; //Tell if it is going forward or backwards
	bool forward_direction_y;
	bool forward_direction_z;
	float velocity; //Velocity to calculate the next step

	bool is_moving; //Tells if moving is still taking place
	float angleCorrection(float distance_theta);
	void verifyRange(float *number, float min, float max);
	//Emotion variable
	bool is_moving_emotional;
	bool is_oscillating_emotional;
};

#endif /* TORSOACTION_H_ */
