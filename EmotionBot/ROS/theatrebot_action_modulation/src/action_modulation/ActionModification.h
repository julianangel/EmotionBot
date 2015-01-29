/*
 * ActionModification.h
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#ifndef ACTIONMODIFICATION_H_
#define ACTIONMODIFICATION_H_

#include <list>
#include <string>
#include <map>
#include <typeinfo>
#include <boost/shared_ptr.hpp>
#include "../general_execution/SimpleActionTrajectoryExecution.h"
#include "../general_description/emotion_description/EmotionProfile.h"
#include "../general_description/parameters_description/parameters_instances/ParameterVelocity.h"
#include "../general_description/parameters_description/parameters_instances/ParameterTime.h"
#include "../general_description/parameters_description/parameters_instances/ParameterAcceleration.h"

using std::string;
using std::list;
using std::map;
using boost::shared_ptr;

class ActionModification {
public:
	ActionModification();
	virtual ~ActionModification();
	/*
	 * This method copies the emotion parameters to each emotions. The final calculation of the velocity
	 * to control the robot is done further because at this point is not possible to know the final distance,
	 * due that here is the ideal position and it does not have any information of the planification system.
	 */
	void addEmotionParameters(string emotion_and_action,
			list<shared_ptr<SimpleActionExecution> > *list_simple_action ,
			map<string,shared_ptr<EmotionProfile> > emotions_profile);
	//This one is used when the planner is going to execute
	void modifySimpleActions(shared_ptr<SimpleActionExecution>simple_action);
	float emotionalFactor(float emotional_intensity, string emotion);
private:
	vector<shared_ptr<EmotionParameter > > searchEmotionParameters(
			shared_ptr<EmotionProfile> emotion_profile, string action_name);
	/*
	 * Here should be a different method for each kind of trajectory modification.
	 * If the method is not implemented the desired modification could not be done.
	 * In case that there is not any desire parameter, it would be used a pre-define values
	 */
	void modifyUsingPreDefinedValues(shared_ptr<SimpleActionExecution> action_execution,
			shared_ptr<EmotionProfile> emotion_profile);
	void modifyUsingVelocity(shared_ptr<SimpleActionExecution>action_execution,
			shared_ptr<EmotionProfile> emotion_profile);
	void modifyUsingTime(shared_ptr<SimpleActionExecution> action_execution,
			shared_ptr<EmotionProfile> emotion_profile);
	void modifyUsingAcceleration(shared_ptr<SimpleActionExecution> action_execution,
			shared_ptr<EmotionProfile> emotion_profile);
};

#endif /* ACTIONMODIFICATION_H_ */
