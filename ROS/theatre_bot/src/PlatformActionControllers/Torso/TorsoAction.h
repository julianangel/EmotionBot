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
protected:
	float desire_angle_to_oscillate;
	//front and back
	float desire_angle_to_move;
	//left to righ
	float desire_angle_to_side;
	bool is_oscillating;
	float delta_time; //milli seconds
	bool forward_direction; //it tells if is going forwards or backwards
	float velocity;

	float angleCorrection(float distance_theta);
};

#endif /* TORSOACTION_H_ */
