/*
 * OscillateShoulderDescription.h
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#ifndef OSCILLATESHOULDERDESCRIPTION_H_
#define OSCILLATESHOULDERDESCRIPTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/OscillateShoulderExecution.h"

class OscillateShoulderDescription: public SimpleActionDescription {
public:
	OscillateShoulderDescription();
	virtual ~OscillateShoulderDescription();
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

#endif /* OSCILLATESHOULDERDESCRIPTION_H_ */
