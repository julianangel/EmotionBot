/*
 * SimpleActionMoveShoulder.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#include "SimpleActionMoveShoulder.h"

SimpleActionMoveShoulder::SimpleActionMoveShoulder() {
	this->action_name = "move_shoulder";
}

SimpleActionMoveShoulder::~SimpleActionMoveShoulder() {
	// TODO Auto-generated destructor stub
}

bool SimpleActionMoveShoulder::MandatoryParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_amplitude")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				Json::FastWriter writer;
				this->parameter_message += writer.write(parameter);
				return true;
			}
	}
	return false;
}

bool SimpleActionMoveShoulder::OptionalParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_time")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				this->parameter_message += "time";
				return true;
			}
			if(parameter_name.compare("parameter_velocity")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				this->parameter_message += "velocity";
				return true;
			}
	}
	return false;
}