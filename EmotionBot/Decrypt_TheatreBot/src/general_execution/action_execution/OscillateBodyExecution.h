/*
 * OscillateBodyExecution.h
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#ifndef OSCILLATEBODYEXECUTION_H_
#define OSCILLATEBODYEXECUTION_H_

#include "../SimpleActionTrajectoryExecution.h"
#include "../../general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "../../general_description/parameters_description/parameters_instances/ParameterTranslation.h"

class OscillateBodyExecution: public SimpleActionTrajectoryExecution {
public:
	OscillateBodyExecution();
	virtual ~OscillateBodyExecution();
	bool executeAction(string platform);
	void setParameterDestination(shared_ptr<PointPositionParameter> parameter_destination);
	shared_ptr<PointPositionParameter> getParameterDestination();

private:
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<PointPositionParameter> parameter_destination;
};

#endif /* OSCILLATEBODYEXECUTION_H_ */
