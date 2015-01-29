/*
 * SimpleActionTrajectoryExecution.h
 *
 *  Created on: May 9, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONTRAJECTORYEXECUTION_H_
#define SIMPLEACTIONTRAJECTORYEXECUTION_H_

#include "SimpleActionExecution.h"
#include "../general_description/parameters_description/parameters_instances/ParameterTranslation.h"

using boost::shared_ptr;

class SimpleActionTrajectoryExecution: public SimpleActionExecution {
public:
	SimpleActionTrajectoryExecution();
	virtual ~SimpleActionTrajectoryExecution();
	void setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();

protected:
	/**
	 * This parameter constrains the trajectory: time, velocity, acceleration.
	 * This parameter could be optional
	 */
	shared_ptr<ParameterTranslation> parameter_translation;

};

#endif /* SIMPLEACTIONTRAJECTORYEXECUTION_H_ */
