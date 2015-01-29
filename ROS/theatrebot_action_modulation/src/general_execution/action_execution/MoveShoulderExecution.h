/*
 * MoveShoulderExecution.h
 *
 *  Created on: Apr 16, 2014
 *      Author: julian
 */

#ifndef MOVESHOULDEREXECUTION_H_
#define MOVESHOULDEREXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterTranslation.h"

class MoveShoulderExecution: public SimpleActionTrajectoryExecution {
public:
	MoveShoulderExecution();
	virtual ~MoveShoulderExecution();
	void setParameterPointPosition(shared_ptr<PointPositionParameter> parameter_position);
	shared_ptr<PointPositionParameter> getParameterPosition();
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage getMessage();
private:
	//Pose???
	shared_ptr<PointPositionParameter> parameter_position;
};

#endif /* MOVESHOULDEREXECUTION_H_ */
