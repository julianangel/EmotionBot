///////////////////////////////////////////////////////////
//  EmotionParameter.cpp
//  Implementation of the Class EmotionParameter
//  Created on:      01-abr-2014 05:53:24 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "EmotionParameter.h"


EmotionParameter::EmotionParameter(){

	emotion_parameter_spacing = 0;
	emotion_parameter_time = 0;
}



EmotionParameter::~EmotionParameter(){

}

float EmotionParameter::getEmotionParameterTime(){
	return this->emotion_parameter_time;
}
void EmotionParameter::setEmotionParameterTime(float emotion_parameter_time){
	this->emotion_parameter_time = emotion_parameter_time;
}

float EmotionParameter::getEmotionParameterSpacing(){
	return this->emotion_parameter_spacing;
}

void EmotionParameter::setEmotionParameterSpacing(float emotion_parameter_spacing){
	this->emotion_parameter_spacing = emotion_parameter_spacing;
}
