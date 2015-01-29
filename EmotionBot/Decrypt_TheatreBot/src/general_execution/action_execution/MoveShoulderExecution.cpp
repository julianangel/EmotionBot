/*
 * MoveShoulderExecution.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: julian
 */

#include "MoveShoulderExecution.h"

MoveShoulderExecution::MoveShoulderExecution() {
	this->action_name = "move_shoulder";
	this->type_action = TypeActionTrajectory;
}

MoveShoulderExecution::~MoveShoulderExecution() {
}


bool MoveShoulderExecution::executeAction(string platform){
	bool result=false;
	if(this->parameter_position!= NULL && this->parameter_translation !=NULL){
		if(platform == "triskar_big"){

		}else if(platform == "triskar_small"){
			cout<<"executing move shoulder"<<endl;
		}
	}
	return result;
}
void MoveShoulderExecution::setParameterPointPosition(boost::shared_ptr<PointPositionParameter> parameter_position){
	this->parameter_position = parameter_position;
}
boost::shared_ptr<PointPositionParameter> MoveShoulderExecution::getParameterPosition(){
	return this->parameter_position;
}
