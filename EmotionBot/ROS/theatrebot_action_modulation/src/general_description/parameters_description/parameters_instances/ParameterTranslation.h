/*
 * ParameterTranslation.h
 *
 *  Created on: Apr 7, 2014
 *      Author: julian
 */

#ifndef PARAMETERTRANSLATION_H_
#define PARAMETERTRANSLATION_H_

#include "../ParameterValue.h"

class ParameterTranslation: public ParameterValue {
public:
	ParameterTranslation();
	virtual ~ParameterTranslation()=0;
};

#endif /* PARAMETERTRANSLATION_H_ */
