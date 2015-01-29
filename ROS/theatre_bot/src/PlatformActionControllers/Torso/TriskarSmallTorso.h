/*
 * TriskarSmallTorso.h
 *
 *  Created on: Jan 27, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLTORSO_H_
#define TRISKARSMALLTORSO_H_

#include "TorsoAction.h"
#include "theatre_bot/TriskarSmallUpper.h"

class TriskarSmallTorso: public TorsoAction {
public:
	TriskarSmallTorso();
	virtual ~TriskarSmallTorso();
	void MoveTorsoAction(Amplitude parameter);
	void OscillateTorsoAction(Amplitude parameter);
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);
	void stopMoveTorsoAction();
	void stopOscillateTorsoAction();
	void callbackUpdateTriskarUpper(const theatre_bot::TriskarSmallUpper::ConstPtr& msg);
	void sendMessage(float position);
private:
	ros::Publisher pub_action_triskar;
	ros::Subscriber sub;

	float max_angle;
	float min_angle;

	float current_angle;

	void initMessageTriskar(theatre_bot::TriskarSmallUpper *message);
};

#endif /* TRISKARSMALLTORSO_H_ */