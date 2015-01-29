///////////////////////////////////////////////////////////
//  ActionChanges.h
//  Implementation of the Class ActionChanges
//  Created on:      01-abr-2014 05:53:23 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef ACTIONCHANGES_H
#define ACTIONCHANGES_H

#include <cstdlib>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../parameters_description/parameters_instances/EmotionParameter.h"
#include "../../types_description/TypeActionEmotionChange.h"

using std::vector;
using boost::shared_ptr;
/**
 * this class containts the changes that should be done to a specific action to
 * show emotion in a general action. For example to show the happines for move, it
 * is necessary to changes several actios as: oscillateshoulder, oscillatemove, etc
 */
class ActionChanges
{

public:
	ActionChanges();
	virtual ~ActionChanges();

	/*
	 * Get the name of the actionto modify
	 */
	string getActionChangesName();
	/*
	 * Sets the action's name to modify
	 */
	void setActionChangesName(string action_changes_name);
	vector<shared_ptr<EmotionParameter> > getActionChangesParameteres();
	void setActionChangesParameter(vector<shared_ptr<EmotionParameter> > action_changes_parameters);
    void setTypeActionEmotion(TypeActionEmotionChange type_action_emotion);
    TypeActionEmotionChange getTypeActionEmotion();
    void addActioChangesParameter(shared_ptr<EmotionParameter> emotion_parameter);

private:
	/**
	 * <font color="#000000">name of the action to modify</font>
	 */
	string action_changes_action;
	vector<shared_ptr<EmotionParameter> > action_changes_parameters;
	/**
	 * This variable says if this actions should have to change their parameters during
	 * its execution
	 */
	TypeActionEmotionChange type_action_emotion;
};
#endif
