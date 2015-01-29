/*
 * Move.h
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#ifndef MOVEBODYEXECUTION_H_
#define MOVEBODYEXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterPosition.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterTranslation.h"
class MoveBodyExecution: public SimpleActionTrajectoryExecution {
public:
	MoveBodyExecution();
	virtual ~MoveBodyExecution();
	void setParameterDestination(shared_ptr<ParameterPosition> parameter_destination);
	shared_ptr<ParameterPosition> getParameterDestination();
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage getMessage();
private:
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<ParameterPosition> parameter_destination;
};

#endif /* MOVE_H_ */
