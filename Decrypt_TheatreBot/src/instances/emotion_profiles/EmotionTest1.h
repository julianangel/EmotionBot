/*
 * EmotionTest1.h
 *
 *  Created on: Apr 15, 2014
 *      Author: julian
 */

#ifndef EMOTIONTEST1_H_
#define EMOTIONTEST1_H_

#include <map>

#include "../../general_description/emotion_description/EmotionProfile.h"

using std::map;

class EmotionTest1 {
public:
	EmotionTest1();
	virtual ~EmotionTest1();

	void createMoveHappy();
	void createMoveSad();
	void createMoveAngry();

	map<string,shared_ptr<EmotionProfile> > getEmotionProfile();


private:
	shared_ptr<EmotionProfile> getEmotionProfileMoveHappy();
	shared_ptr<EmotionProfile> getEmotionProfileMoveAngry();
	shared_ptr<EmotionProfile> getEmotionProfileMoveSad();
	shared_ptr<EmotionProfile> getEmotionProfileMoveFear();
	shared_ptr<EmotionProfile> getEmotionProfileMoveCuriosity();
	shared_ptr<EmotionProfile> getEmotionProfileMoveEmbarrassment();
	shared_ptr<EmotionProfile> getEmotionProfileMoveDisgust();
	//Happy
	shared_ptr<EmotionProfile> emotion_profile_happy_move;
	shared_ptr<EmotionProfile> emotion_profile_happy_oscillate_shoulder;
	//Angry
	shared_ptr<EmotionProfile> emotion_profile_angry_move;
	shared_ptr<EmotionProfile> emotion_profile_angry_oscillate_shoulder;
	//Sad
	shared_ptr<EmotionProfile> emotion_profile_sad_move;
	shared_ptr<EmotionProfile> emotion_profile_sad_oscillate_shoulder;
	//Fear
	shared_ptr<EmotionProfile> emotion_profile_fear_move;
	shared_ptr<EmotionProfile> emotion_profile_fear_oscillate_shoulder;
	//Curiosity
	shared_ptr<EmotionProfile> emotion_profile_curiosity_move;
	shared_ptr<EmotionProfile> emotion_profile_curiosity_oscillate_shoulder;
	//Embarrassment
	shared_ptr<EmotionProfile> emotion_profile_embarrassment_move;
	shared_ptr<EmotionProfile> emotion_profile_embarrassment_oscillate_shoulder;
	//Disgust
	shared_ptr<EmotionProfile> emotion_profile_disgust_move;
	shared_ptr<EmotionProfile>emotion_profile_disgust_oscillate_shoulder;

};

#endif /* EMOTIONTEST1_H_ */
