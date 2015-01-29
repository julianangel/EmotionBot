///////////////////////////////////////////////////////////
//  EmotionProfile.h
//  Implementation of the Class EmotionProfile
//  Created on:      01-abr-2014 05:53:24 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef EMOTIONPROFILE_H
#define EMOTIONPROFILE_H

#include "ActionChanges.h"

using boost::shared_ptr;
/**
 * <font color="#000000">This class encasulaptes each emotion for each simple
 * action</font>
 */
class EmotionProfile
{

public:
	EmotionProfile();
	virtual ~EmotionProfile();

	string getEmotionProfileName();
	void setEmotionProfileName(string emotion_profile_name);
	string getEmotionProfileAction();
	void setEmotionProfileAction(string emotion_profile_action);
	string getEmotionProfileEmotion();
	void setEmotionProfileEmotion(string emotion_profile_emotion);
	string getEmotionProfileDescription();
	void setEmotionProfileDescription(string emotion_profile_description);
	vector<shared_ptr<ActionChanges> > getEmotionProfileActions();
	void setEmotionProfile(vector<shared_ptr<ActionChanges> > emotion_profile_actions);
	void addEmotionProfileActionChanges(shared_ptr<ActionChanges> emotion_profile_action_changes);

private:
	/**
	 * <font color="#000000">it is the name of the emotion that will be described by
	 * this profile</font>
	 */
	string emotion_profile_name;
	/**
	 * <font color="#000000">this describes to which actions is related is this
	 * emotions. For example to show happiness while is moving the robot should add
	 * other simple actions and modify the action</font>
	 */
	string emotion_profile_action;
	/**
	 * This is the base action used in this profile
	 */
	string emotion_profile_emotion;
	/**
	 * <font color="#000000">description of the emotion profile</font>
	 */
	string emotion_profile_description;
	vector<shared_ptr<ActionChanges> > emotion_profile_actions;

};
#endif // !defined(EA_03ADBB89_FD9B_4b44_AAD2_C4F9D640F0BE__INCLUDED_)
