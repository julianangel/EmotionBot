/*
 * OscillateTorsoExecution.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#include "OscillateTorsoExecution.h"

OscillateTorsoExecution::OscillateTorsoExecution() {
	this->action_name = "oscillate_torso";

}

OscillateTorsoExecution::~OscillateTorsoExecution() {

}



void OscillateTorsoExecution::setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateTorsoExecution::getParameterDestination(){
	return this->parameter_destination;
}

theatrebot_action_modulation::ActionExecutionActionDescriptionMessage
OscillateTorsoExecution::getMessage(){
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage temp;
	temp.action_name.data = this->action_name;
	temp.action_name.data = this->action_name;
	if(this->type_action==TypeActionEmotional){
		temp.action_type.data = "emotional";
	}else if(this->type_action == TypeActionMandatory){
		temp.action_type.data = "mandatory";
	}
	temp.action_is_principal.data = this->action_is_principal;
	temp.desire_position.type_parameter.data = "point_position";
	temp.desire_position.desire_position.position.x =
			parameter_destination->getXPosition();
	temp.desire_position.desire_position.position.y =
			parameter_destination->getYPosition();
	temp.desire_position.desire_position.orientation =
			tf::createQuaternionMsgFromYaw(parameter_destination->getThetaPosition());
	//TODO implement for the othres parameters
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
