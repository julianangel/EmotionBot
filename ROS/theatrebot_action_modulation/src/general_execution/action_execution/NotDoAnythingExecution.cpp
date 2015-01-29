/*
 * NotDoAnythingExecution.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: julian
 */

#include "NotDoAnythingExecution.h"

NotDoAnythingExecution::NotDoAnythingExecution() {
	this->action_name = "not_do_anything";

}

NotDoAnythingExecution::~NotDoAnythingExecution() {
	// TODO Auto-generated destructor stub
}


theatrebot_action_modulation::ActionExecutionActionDescriptionMessage
NotDoAnythingExecution::getMessage(){
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage temp;
	temp.action_name.data = this->action_name;
	temp.action_type.data = "mandatory";
	temp.action_is_principal.data = this->action_is_principal;
	return temp;
}
