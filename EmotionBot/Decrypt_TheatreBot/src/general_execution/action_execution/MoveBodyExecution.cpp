/*
 * Move.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#include "MoveBodyExecution.h"

MoveBodyExecution::MoveBodyExecution() {
	this->action_name = "move_body";
	this->type_action = TypeActionTrajectory;
}

MoveBodyExecution::~MoveBodyExecution() {
}

/**
 * This command knows which driver execute to perform the action in the correct platform
 */
bool MoveBodyExecution::executeAction(string platform){
	bool result=false;
	if(platform == "triskar_big"){


	}else if(platform == "triskar_small"){
		cout<<"executing move body: ";
		if(typeid(*(this->parameter_destination)).name()==typeid(PointPositionParameter).name()){
			boost::shared_ptr<PointPositionParameter> temp
			= boost::static_pointer_cast<PointPositionParameter>(this->parameter_destination);
			cout<<temp->getXPosition();
			cout<<"...";
		}
		cout<<endl;
	}
	return result;
}

void MoveBodyExecution::setParameterDestination(
		boost::shared_ptr<ParameterPosition> parameter_destination){
	this->parameter_destination = parameter_destination;
}
boost::shared_ptr<ParameterPosition> MoveBodyExecution::getParameterDestination(){
	return this->parameter_destination;
}
