/*
 * OscillateShoulderExecution.cpp
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#include "OscillateShoulderExecution.h"

OscillateShoulderExecution::OscillateShoulderExecution() {
	this->action_name = "oscillate_shoulder";
	this->type_action = TypeActionTrajectory;
}

OscillateShoulderExecution::~OscillateShoulderExecution() {
}

bool OscillateShoulderExecution::executeAction(string platform){
	bool result=false;
	if(this->parameter_destination!= NULL && this->parameter_translation !=NULL){
		if(platform == "triskar_big"){


		}else if(platform == "triskar_small"){
			cout<<"executing oscillate shoulder: ";
			if(typeid(*(this->parameter_translation)).name()==typeid(ParameterVelocity).name()){
				cout<<"doing something"<<endl;
			}
		}
	}
	return result;

}
void OscillateShoulderExecution::setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateShoulderExecution::getParameterDestination(){
	return this->parameter_destination;
}
