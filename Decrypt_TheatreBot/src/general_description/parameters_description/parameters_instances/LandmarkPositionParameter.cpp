///////////////////////////////////////////////////////////
//  LandmarkPosition.cpp
//  Implementation of the Class LandmarkPosition
//  Created on:      01-abr-2014 05:53:24 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "LandmarkPositionParameter.h"


LandmarkPositionParameter::LandmarkPositionParameter(){
	landmark_type = TypeLandmarkNone;
}



LandmarkPositionParameter::~LandmarkPositionParameter(){

}


TypeLandmark LandmarkPositionParameter::getLandmarType(){

	return  landmark_type;
}


void LandmarkPositionParameter::setLandmarkType(TypeLandmark landmark_type){

	this->landmark_type = landmark_type;
}

float LandmarkPositionParameter::getDistanceToDesirePosition(float robot_poistion){
	return 0;
}
