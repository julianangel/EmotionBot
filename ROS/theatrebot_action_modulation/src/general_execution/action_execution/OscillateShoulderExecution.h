/*
 * OscillateShoulderExecution.h
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#ifndef OSCILLATESHOULDEREXECUTION_H_
#define OSCILLATESHOULDEREXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterVelocity.h"

class OscillateShoulderExecution: public SimpleActionTrajectoryExecution {
public:
	OscillateShoulderExecution();
	virtual ~OscillateShoulderExecution();
	void setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination);
	shared_ptr<PointPositionParameter> getParameterDestination();
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage getMessage();
private:
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<PointPositionParameter> parameter_destination;
};

#endif /* OSCILLATESHOULDEREXECUTION_H_ */
