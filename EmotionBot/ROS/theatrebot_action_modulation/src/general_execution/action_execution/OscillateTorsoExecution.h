/*
 * OscillateTorsoExecution.h
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#ifndef OSCILLATETORSOEXECUTION_H_
#define OSCILLATETORSOEXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterVelocity.h"

class OscillateTorsoExecution: public SimpleActionTrajectoryExecution  {
public:
	OscillateTorsoExecution();
	virtual ~OscillateTorsoExecution();
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

#endif /* OSCILLATETORSOEXECUTION_H_ */
