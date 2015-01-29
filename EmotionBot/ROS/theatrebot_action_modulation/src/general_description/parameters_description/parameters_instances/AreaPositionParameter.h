///////////////////////////////////////////////////////////
//  AreaPosition.h
//  Implementation of the Class AreaPosition
//  Created on:      01-abr-2014 05:53:23 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef AREAPOSITIONPARAMETER_H
#define AREAPOSITIONPARAMETER_H

#include <cstdlib>
#include <string>
#include "ParameterPosition.h"

using std::string;
/**
 * <font color="#000000">This is a specialization of position</font>
 */
class AreaPositionParameter : public ParameterPosition
{

public:
	AreaPositionParameter();
	virtual ~AreaPositionParameter();
	string getAreaType();
	void setAreaType(string area_type);
	float getDistanceToDesirePosition(float robot_poistion);
private:
	string area_type;

};
#endif // !defined(EA_C5A153CC_9C81_4e88_9668_31B0D2CF8408__INCLUDED_)
