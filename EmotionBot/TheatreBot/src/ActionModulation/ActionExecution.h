/*
 * ActionExecution.h
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 */

#ifndef ACTIONEXECUTION_H_
#define ACTIONEXECUTION_H_

#include <typeinfo>

#include "MessageType.h"

#include "../ContextDescription/CompositeContextDescription.h"
#include "../ContextDescription/SimpleContextDescription.h"

class ActionExecution {
public:
	ActionExecution();
	virtual ~ActionExecution();
	void changeInEmotion(AbstractContextDescription * context);
	void changeInIntensity(AbstractContextDescription * context);
	void changeInAction(AbstractContextDescription * context);
	void stopAction();
	void stopEmotionalActions();
	//Action synchronization
	void actionSynchronization(std::string action_name);
	//Emotion synchronization
	void emotionSynchronization(std::string action_name);

	void lock();
	void unlock();

	std::vector<std::string> getListActionsToStop();
	void cleanListActionsToStop();
	std::vector<std::string> getListEmotionalActionToSynch();
	void cleanListEmotionalActionToSynch();

	std::map<std::string,std::string> generateParameterMessage();
	std::map<std::string,std::string> generateEmotionalParameterMessage();

	void printQueue();

private:
	void propagateActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context);
	void propagateEmotionalActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context);
	//this cleans the emotions and current action queue
	void deleteActionsQueue();
	void sendEmotionalMessages();
	void sendActionMessages();
	void addEmotionalAction(SimpleContextDescription * temp_context);
	std::map<std::string,SimpleContextDescription *> current_actions;
	std::map<std::string,SimpleContextDescription *> current_emotional_actions;
	std::vector<std::string> list_actions_to_stop;
	std::vector<std::string> list_actions_to_emotional_synch;

	bool updating_data;
};

#endif /* ACTIONEXECUTION_H_ */
