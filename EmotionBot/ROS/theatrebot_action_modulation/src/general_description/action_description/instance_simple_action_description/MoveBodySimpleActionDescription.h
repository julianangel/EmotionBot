/*
 * MoveSimpleActionDescription.h
 *
 *  Created on: Apr 16, 2014
 *      Author: julian
 */

#ifndef MOVESIMPLEACTIONDESCRIPTION_H_
#define MOVESIMPLEACTIONDESCRIPTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/MoveBodyExecution.h"

class MoveBodySimpleActionDescription: public SimpleActionDescription {
public:
	MoveBodySimpleActionDescription();
	virtual ~MoveBodySimpleActionDescription();
	list<shared_ptr<SimpleActionExecution> > Analyze(void);
	void setParameterPosition(shared_ptr<ParameterPosition> parameter_destination);
	shared_ptr<ParameterPosition> getParameterPosition();
	void setParameterTrnaslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();

private:
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<ParameterPosition>parameter_destination;
	/**
	 * This parameter constrains the trajectory: time, velocity, acceleration.
	 * This parameter could be optional
	 */
	shared_ptr<ParameterTranslation> parameter_translation;
};

#endif /* MOVESIMPLEACTIONDESCRIPTION_H_ */
