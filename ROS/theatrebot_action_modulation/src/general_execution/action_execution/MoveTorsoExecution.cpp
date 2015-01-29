/*
 * MoveTorsoExecution.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#include "MoveTorsoExecution.h"

MoveTorsoExecution::MoveTorsoExecution() {
	this->action_name = "move_torso";
}

MoveTorsoExecution::~MoveTorsoExecution() {
	// TODO Auto-generated destructor stub
}

void MoveTorsoExecution::setParameterPointPosition(boost::shared_ptr<PointPositionParameter> parameter_position){
	this->parameter_position = parameter_position;
}

boost::shared_ptr<PointPositionParameter> MoveTorsoExecution::getParameterPosition(){
	return this->parameter_position;
}

theatrebot_action_modulation::ActionExecutionActionDescriptionMessage
MoveTorsoExecution::getMessage(){
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage temp;
	//TODO implement for the others parameters
	temp.action_name.data = this->action_name;
	temp.action_name.data = this->action_name;
	if(this->type_action==TypeActionEmotional){
		temp.action_type.data = "emotional";
	}else if(this->type_action == TypeActionMandatory){
		temp.action_type.data = "mandatory";
	}
	temp.action_is_principal.data = this->action_is_principal;
	if(typeid(*parameter_position).name()==typeid(PointPositionParameter).name()){
		shared_ptr<PointPositionParameter> temp_parameter_position
			=boost::static_pointer_cast<PointPositionParameter>(parameter_position);
		temp.desire_position.type_parameter.data = "point_position";
		temp.desire_position.desire_position.position.x =
				temp_parameter_position->getXPosition();
		temp.desire_position.desire_position.position.y =
				temp_parameter_position->getYPosition();
		temp.desire_position.desire_position.orientation =
				tf::createQuaternionMsgFromYaw(temp_parameter_position->getThetaPosition());
	}
	//TODO implement for the others parameters
	if(typeid(*parameter_translation).name()==typeid(ParameterVelocity).name()){
		temp.trajectory_characteristic.type_parameter.data = "velocity_parameter";
		shared_ptr<ParameterVelocity> temp_parameter_velocity
			=boost::static_pointer_cast<ParameterVelocity>(parameter_translation);
		temp.trajectory_characteristic.trajectory_characteristic.linear.x
				= temp_parameter_velocity->getVelocityX();
		temp.trajectory_characteristic.trajectory_characteristic.linear.y
				= temp_parameter_velocity->getVelocityY();
		temp.trajectory_characteristic.trajectory_characteristic.angular.x
				= temp_parameter_velocity->getVelocityTheta();
	}
	//Emotion
	for(vector<shared_ptr<EmotionParameter> >::iterator it = emotion_changes.begin();
			it != emotion_changes.end(); it++){
		theatrebot_action_modulation::EmotionParametersMessage temp_emotion;
		temp_emotion.timing = (*it)->getEmotionParameterTime();
		temp_emotion.spacing = (*it)->getEmotionParameterSpacing();
		temp.emotion_parameters.push_back(temp_emotion);
	}
	return temp;
}
