///////////////////////////////////////////////////////////
//  LandmarkPosition.h
//  Implementation of the Class LandmarkPosition
//  Created on:      01-abr-2014 05:53:24 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef LANDMARKPOSITIONPARAMETER_H
#define LANDMARKPOSITIONPARAMETER_H

#include <cstdlib>
#include "../../../types_description/TypeLandmark.h"
#include "ParameterPosition.h"

class LandmarkPositionParameter : public ParameterPosition
{

public:
	LandmarkPositionParameter();
	virtual ~LandmarkPositionParameter();
	TypeLandmark getLandmarType();
	void setLandmarkType(TypeLandmark landmark_type);
	float getDistanceToDesirePosition(float robot_poistion);
private:
	/**
	 * <font color="#000000">It could be: object, person, place, stage direction</font>
	 */
	TypeLandmark landmark_type;

};
#endif // !defined(EA_7037D24F_751E_463f_AC08_1F929ACCC86C__INCLUDED_)
