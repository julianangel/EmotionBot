/*
 * TriskarSmallBody.h
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLBODY_H_
#define TRISKARSMALLBODY_H_

#include "BodyAction.h"
#include "TriskarPlanner.h"
#include "theatre_bot/TriskarVelocity.h"
#include "theatre_bot/OdometryTriskar.h"
#include "std_msgs/Char.h"

class TriskarSmallBody: public BodyAction {
public:
	TriskarSmallBody();
	virtual ~TriskarSmallBody();

	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);

	void MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position);
	void OscillateBodyAction(Amplitude parameter);
	void stopMoveBodyAction();
	void stopOscillateBodyAction();
	void synchEmotionMove();
	void synchEmotionOscillate();
	void setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);


	void callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg);
private:
	float reduce_linear_velocity; //This variable tells the distance that it should to start slowing down to not pass over the point
	float reduce_angular_velocity;//This variable tells the distance that it should to start slowing down to not pass over the desire angle
	float maximum_error_x;
	float maximum_error_y;
	float maximum_error_theta;
	bool has_arrived;
	float emotional_distance; //this is the new distance to follow
	float initial_emotional_distance;//This gets the distance when the emotional parameters arrived


	TriskarPlanner triskar_planner;

	ros::Publisher pub_action_triskar;
	ros::Publisher pub_command_triskar;
	ros::Subscriber sub;
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void generateEmotionalActionMove();
	void generateEmotionalVelocityMove();
};

#endif /* TRISKARSMALLBODY_H_ */
