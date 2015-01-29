/*
 * MoveShoulderSimpleActionDescription.h
 *
 *  Created on: Apr 17, 2014
 *      Author: julian
 */

#ifndef MOVESHOULDERSIMPLEACTIONDESCRIPTION_H_
#define MOVESHOULDERSIMPLEACTIONDESCRIPTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/MoveShoulderExecution.h"

class MoveShoulderSimpleActionDescription: public SimpleActionDescription {
public:
	MoveShoulderSimpleActionDescription();
	virtual ~MoveShoulderSimpleActionDescription();
	list< shared_ptr<SimpleActionExecution> > Analyze();
	void setParameterPointPosition(shared_ptr<PointPositionParameter> parameter_position);
	shared_ptr<PointPositionParameter> getParameterPosition();
	void setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();
private:
	//Pose???
	shared_ptr<PointPositionParameter> parameter_position;
	/**
	 * This parameter constrains the trajectory: time, velocity, acceleration.
	 * This parameter could be optional
	 */
	shared_ptr<ParameterTranslation> parameter_translation;
};

#endif /* MOVESHOULDERSIMPLEACTIONDESCRIPTION_H_ */
