///////////////////////////////////////////////////////////
//  ParameterVelocity.h
//  Implementation of the Class ParameterVelocity
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef PARAMETERVELOCITY_H
#define PARAMETERVELOCITY_H

#include "ParameterTranslation.h"

class ParameterVelocity : public ParameterTranslation
{

public:
	ParameterVelocity();
	virtual ~ParameterVelocity();
	float getVelocityX();
	float getVelocityY();
	float getVelocityTheta();
	void setVelocityX(float velocity_x);
	void setVelocityY(float velocity_y);
	void setVelocityTheta(float velocity_theta);
	void setVelocity(float velocity_x,float velocity_y,float velocity_theta);

private:
	float velocity_x;
	float velocity_y;
	float velocity_theta;

};
#endif // !defined(EA_ADED46FD_FAA6_429c_98D2_167312C8A2B6__INCLUDED_)
