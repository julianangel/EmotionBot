/*
 * MoveTorsoSimpleAction.h
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#ifndef MOVETORSOSIMPLEACTION_H_
#define MOVETORSOSIMPLEACTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/MoveTorsoExecution.h"

class MoveTorsoSimpleAction: public SimpleActionDescription {
public:
	MoveTorsoSimpleAction();
	virtual ~MoveTorsoSimpleAction();
	list< shared_ptr<SimpleActionExecution> > Analyze();
	void setParameterPointPosition(shared_ptr<PointPositionParameter> parameter_position);
	shared_ptr<PointPositionParameter> getParameterPosition();
	void setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();

private:
	shared_ptr<PointPositionParameter> parameter_position;
	shared_ptr<ParameterTranslation> parameter_translation;

};

#endif /* MOVETORSOSIMPLEACTION_H_ */
