/*
 * EmotionParser.h
 *
 *  Created on: Jan 28, 2015
 *      Author: julian
 */

#ifndef EMOTIONPARSER_H_
#define EMOTIONPARSER_H_

#include "../json/json/json.h"
#include "../Parameters/EmotionalParameters/EmotionMovementParameter.h"

class EmotionParser {
public:
	EmotionParser();
	virtual ~EmotionParser();
	static bool parse(std::string message, std::vector<EmotionMovementParameter> parameters);
};

#endif /* EMOTIONPARSER_H_ */
