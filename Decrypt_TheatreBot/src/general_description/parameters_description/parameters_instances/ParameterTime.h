///////////////////////////////////////////////////////////
//  ParameterTime.h
//  Implementation of the Class ParameterTime
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef PARAMETERTIME_H
#define PARAMETERTIME_H

#include "ParameterTranslation.h"

/**
 * <font color="#000000">This parameter is used when the time is important, thus
 * all the calculations will be done in base the time and not in term of
 * velocity</font>
 */
class ParameterTime : public ParameterTranslation
{

public:
	ParameterTime();
	virtual ~ParameterTime();
	float getTimeValue();
	void setTimeValue(float time_value);

private:
	float time_value;

};
#endif // !defined(EA_0F2BE06F_D871_46d1_A572_2EC67845800D__INCLUDED_)
