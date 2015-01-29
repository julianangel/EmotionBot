/*
 * ActionChanges.h
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#ifndef ACTIONCHANGES_H_
#define ACTIONCHANGES_H_

#include <cstdlib>
#include <vector>

#include "../Parameters/EmotionalParameters/EmotionParameter.h"


using std::string;
using std::vector;
/**
 * this class containts the changes that should be done to a specific action to
 * show emotion in a general action. For example to show the happines for move, it
 * is necessary to changes several actios as: oscillateshoulder, oscillatemove, etc
 */
class ActionChanges {
public:
	ActionChanges();
	virtual ~ActionChanges();

	/*
	 * It gives the JSON with all the parameters
	 * */
	string getJSONParameters();
	void setActionThatModyfies(string action_name);
	string getActionThatModyfies();
	vector<EmotionParameter *> copyVectorParameters();
	vector<EmotionParameter *> getVectorParameters();
	void setVectorParameters(vector<EmotionParameter *> parameters);
	void addEmotionParameter(EmotionParameter *parameter);
	void setReference(float reference);
	void setRepetition(bool repeat);
	float getReference();
	bool getRepetition();
	void clearVectorParameters();

private:
	//Action that should be modify
	string action_that_changes;
	//list of parameters associated to this action
	vector<EmotionParameter *> action_emotion_parameters;
	//Bool this tells if the changes in the action should be repeated
	bool repeat;
	//This says the intervals to repeat the action
	float reference;
};

#endif /* ACTIONCHANGES_H_ */
