///////////////////////////////////////////////////////////
//  EmotionParameter.h
//  Implementation of the Class EmotionParameter
//  Created on:      01-abr-2014 05:53:24 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef EMOTIONPARAMETER_H
#define EMOTIONPARAMETER_H

#include "../Parameter.h"

/**
 * <font color="#000000">This class contains additional information as the human
 * interpretation of the value, and its interpretation in numbers</font>
 */
class EmotionParameter : public Parameter
{

public:
	EmotionParameter();
	virtual ~EmotionParameter();

	float getEmotionParameterTime();
	/*
	 * set the time in which the modification should be done. The time is in milliseconds.
	 */
	void setEmotionParameterTime(float emotion_parameter_time);
	float getEmotionParameterSpacing();
	/*
	 * set the space between the two points
	 */
	void setEmotionParameterSpacing(float emotion_parameter_spacing);

private:
	/*
	 * Time in milliseconds
	 */
	float emotion_parameter_time;
	/*
	 * Space between two points, in millimeters
	 */
	float emotion_parameter_spacing;

};
#endif // !defined(EMOTION_PARAMETER)
