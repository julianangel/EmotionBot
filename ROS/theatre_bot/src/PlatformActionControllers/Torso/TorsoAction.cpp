/*
 * TorsoAction.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: julian
 */

#include "TorsoAction.h"

TorsoAction::TorsoAction() {
	desire_angle_to_oscillate = 0;
	desire_angle_to_move = 0;
	delta_time = 100;
	is_oscillating = false;
	forward_direction = true;
	velocity = 0;

}

TorsoAction::~TorsoAction() {
	// TODO Auto-generated destructor stub
}

float TorsoAction::angleCorrection(float distance_theta){
	if(distance_theta>M_PI){
		distance_theta= distance_theta-2.0*M_PI;
	}else if(distance_theta<-M_PI){
		distance_theta = distance_theta+2.0*M_PI;
	}
	return distance_theta;
}

float TorsoAction::updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle){
	float max_angle_to_oscillate = desire_angle_to_move + desire_angle_to_oscillate;
	float min_angle_to_oscillate = desire_angle_to_move - desire_angle_to_oscillate;
	if(max_angle_to_oscillate>max_angle){
		max_angle_to_oscillate = max_angle;
	}
	if(min_angle_to_oscillate<min_angle){
		min_angle_to_oscillate = min_angle;
	}
	//float distance_theta = current_angle - desire_angle_to_move;
	//distance_theta = angleCorrection(distance_theta);
	if(forward_direction){
		if(current_angle >= max_angle_to_oscillate){
			forward_direction = !forward_direction;
			return desire_velocity * -1.0;
		}
	}else{
		desire_velocity = -1.0*desire_velocity;
		if(current_angle <= min_angle_to_oscillate){
			forward_direction = !forward_direction;
			return desire_velocity * -1.0;
		}
	}
	return desire_velocity;
}
