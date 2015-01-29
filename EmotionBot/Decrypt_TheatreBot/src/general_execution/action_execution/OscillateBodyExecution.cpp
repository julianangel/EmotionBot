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
	this->type_action = TypeActionTrajectory;
}

OscillateBodyExecution::~OscillateBodyExecution() {
}
bool OscillateBodyExecution::executeAction(string platform){
	bool result = false;
	if(this->parameter_destination!= NULL && this->parameter_translation !=NULL){
		if(platform == "triskar_big"){

		}else if(platform == "triskar_small"){
			cout<<" executing oscillate body"<<endl;
		}
	}

	return result;
}
void OscillateBodyExecution::setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateBodyExecution::getParameterDestination(){
	return this->parameter_destination;
}

