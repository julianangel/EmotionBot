/*
 * MoveTorsoExecution.h
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#ifndef MOVETORSOEXECUTION_H_
#define MOVETORSOEXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterVelocity.h"

class MoveTorsoExecution: public SimpleActionTrajectoryExecution {
public:
	MoveTorsoExecution();
	virtual ~MoveTorsoExecution();
	void setParameterPointPosition(shared_ptr<PointPositionParameter> parameter_position);
	shared_ptr<PointPositionParameter> getParameterPosition();
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage getMessage();

private:
	shared_ptr<PointPositionParameter> parameter_position;
};

#endif /* MOVETORSOEXECUTION_H_ */
