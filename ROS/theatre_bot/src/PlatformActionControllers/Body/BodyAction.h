/*
 * BodyAction.h
 *
 *  Created on: Jan 30, 2015
 *      Author: julian
 */

#ifndef BODYACTION_H_
#define BODYACTION_H_

#include "ros/ros.h"
#include "math.h"
#include "../../Parameters/MovementParameters/Circle.h"
#include "../../Parameters/MovementParameters/Position.h"
#include "../../Parameters/MovementParameters/Point.h"
#include "../../Parameters/MovementParameters/Square.h"
#include "../../Parameters/MovementParameters/Landmark.h"

class BodyAction {
public:
	BodyAction();
	virtual ~BodyAction();
private:
	//Move

	//Oscillate
	float yaw;
	float pitch;
	float roll;
	float desire_angle_to_oscillate_yaw;
	float desire_angle_to_oscillate_pitch;
	float desire_angle_to_oscillate_roll;
	bool forward_direction_yaw;
	bool forward_direction_pitch;
	bool forward_direction_roll;
};

#endif /* BODYACTION_H_ */
