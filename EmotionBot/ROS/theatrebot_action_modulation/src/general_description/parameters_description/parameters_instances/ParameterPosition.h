///////////////////////////////////////////////////////////
//  ParameterPosition.h
//  Implementation of the Class ParameterPosition
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef PARAMETERPOSITION_H
#define PARAMETERPOSITION_H

#include <cstdlib>
#include "../ParameterValue.h"

/**
 * <font color="#000000">This class describes a position parameters, this makes
 * easy the description of position and the parameters, instead of adding three
 * parameters to specify where to go, it could be embembed in one</font>
 */
class ParameterPosition : public ParameterValue
{

public:
	ParameterPosition();
	virtual ~ParameterPosition()=0;/*
	 * This method returns the distance from the robot's position, to
	 * the objective positions.
	 * This distance is used to make the modulation of
	 */
	virtual float getDistanceToDesirePosition(float robot_poistion)=0;

};
#endif // !defined(EA_8C43EBDB_8555_4dc0_BCD4_CD3AE5FEA2D4__INCLUDED_)
