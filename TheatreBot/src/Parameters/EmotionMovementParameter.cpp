/*
 * EmotionMovementParameter.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#include "EmotionMovementParameter.h"

EmotionMovementParameter::EmotionMovementParameter() {
	spacing = 0;
	timing = 0;

}

EmotionMovementParameter::~EmotionMovementParameter() {
	std::cout<<"parameter delete"<<std::endl;
}

float EmotionMovementParameter::getEmotionParameterTime(){
	return this->timing;
}
void EmotionMovementParameter::setEmotionParameterTime(float emotion_parameter_time){
	this->timing = emotion_parameter_time;
}

float EmotionMovementParameter::getEmotionParameterSpacing(){
	return this->spacing;
}

void EmotionMovementParameter::setEmotionParameterSpacing(float emotion_parameter_spacing){
	this->spacing = emotion_parameter_spacing;
}
