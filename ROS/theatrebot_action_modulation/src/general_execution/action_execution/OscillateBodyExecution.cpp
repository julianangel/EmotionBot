/*
 * OscillateBodyExecution.cpp
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#include "OscillateBodyExecution.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterVelocity.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"

OscillateBodyExecution::OscillateBodyExecution() {
	this->action_name = "oscillate_body";
}

OscillateBodyExecution::~OscillateBodyExecution() {
}

void OscillateBodyExecution::setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateBodyExecution::getParameterDestination(){
	return this->parameter_destination;
}

theatrebot_action_modulation::ActionExecutionActionDescriptionMessage
OscillateBodyExecution::getMessage(){
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
	ROS_INFO("parameter: %f, quaternion: %f %f %f %f", parameter_destination->getThetaPosition(),
			temp.desire_position.desire_position.orientation.x,temp.desire_position.desire_position.orientation.y,
			temp.desire_position.desire_position.orientation.z,temp.desire_position.desire_position.orientation.w);
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

