/*
 * OscillateTorsoSimpleAction.h
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#ifndef OSCILLATETORSOSIMPLEACTION_H_
#define OSCILLATETORSOSIMPLEACTION_H_


#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/OscillateTorsoExecution.h"

class OscillateTorsoSimpleAction: public SimpleActionDescription  {
public:
	OscillateTorsoSimpleAction();
	virtual ~OscillateTorsoSimpleAction();
	list<shared_ptr<SimpleActionExecution> > Analyze(void);
	void setParameterPointPosition(shared_ptr<PointPositionParameter> parameter_destination);
	shared_ptr<PointPositionParameter> getParameterPosition();
	void setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();

private:
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<PointPositionParameter> parameter_destination;
	/**
	 * This parameter constrains the trajectory: time, velocity, acceleration.
	 * This parameter could be optional
	 */
	shared_ptr<ParameterTranslation> parameter_translation;
};

#endif /* OSCILLATETORSOSIMPLEACTION_H_ */
