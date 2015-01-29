///////////////////////////////////////////////////////////
//  ParameterAcceleration.h
//  Implementation of the Class ParameterAcceleration
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef PARAMETERACCELERATION_H
#define PARAMETERACCELERATION_H

#include "../../../types_description/TypeAcceleration.h"
#include "ParameterTranslation.h"

class ParameterAcceleration : public ParameterTranslation
{

public:
	ParameterAcceleration();
	virtual ~ParameterAcceleration();
	float getAccelerationX();
	void setAccelerationX(float acceleration_x);
	float getAccelerationY();
	void setAccelerationY(float acceleration_y);
	float getAccelerationTheta();
	void setAccelerationTheta(float acceleration_theta);
	void setAcceleration(float acceleration_x,float acceleration_y,float acceleration_theta);
	TypeAcceleration getAccelerationType();
	void setAccelerationType(TypeAcceleration acceleration_type);

private:
	float acceleration_x;
	float acceleration_y;
	float acceleration_theta;
	TypeAcceleration acceleration_type;

};
#endif // !defined(EA_EFF79962_C3B9_4d9d_9816_1F22CE781A82__INCLUDED_)
