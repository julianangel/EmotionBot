/*
 * NotDoAnythingExecution.h
 *
 *  Created on: Jul 18, 2014
 *      Author: julian
 */

#ifndef NOTDOANYTHINGEXECUTION_H_
#define NOTDOANYTHINGEXECUTION_H_

#include "../SimpleActionExecution.h"

class NotDoAnythingExecution: public SimpleActionExecution  {
public:
	NotDoAnythingExecution();
	virtual ~NotDoAnythingExecution();
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage getMessage();
};

#endif /* NOTDOANYTHINGEXECUTION_H_ */
