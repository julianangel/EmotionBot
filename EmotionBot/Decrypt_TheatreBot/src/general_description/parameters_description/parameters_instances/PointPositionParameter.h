///////////////////////////////////////////////////////////
//  PointPosition.h
//  Implementation of the Class PointPosition
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef POINTPOSITIONPARAMETER_H
#define POINTPOSITIONPARAMETER_H

#include "ParameterPosition.h"

class PointPositionParameter : public ParameterPosition
{

public:
	PointPositionParameter();
	virtual ~PointPositionParameter();
	float getXPosition();
	void setXPosition(float x_position);
	float getYPosition();
	void setYPosition(float y_position);
	float getThetaPosition();
	void setThetaPosition(float theta_position);
	void setPointPosition(float x_position, float y_position,float theta_poisition);
	float getDistanceToDesirePosition(float robot_poistion);
private:
	float x_position;
	float y_position;
	float theta_position;

};
#endif // !defined(EA_D6360FE0_ACC7_46da_A21E_BF383A5FAA0E__INCLUDED_)
