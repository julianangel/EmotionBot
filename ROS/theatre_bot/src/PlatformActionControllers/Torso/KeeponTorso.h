/*
 * KeeponTorso.h
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#ifndef KEEPONTORSO_H_
#define KEEPONTORSO_H_

#include "TorsoAction.h"
#include "../TypePlatform.h"
#include "theatre_bot/KeeponMessage.h"

class KeeponTorso: public TorsoAction {
public:
	KeeponTorso();
	virtual ~KeeponTorso();
	void MoveTorsoAction(Amplitude parameter);
	void OscillateTorsoAction(Amplitude parameter);
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);
	void callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg);
	void stopMoveTorsoAction();
	void stopOscillateTorsoAction();
private:
	ros::Publisher pub_action_keepon;

	ros::Subscriber sub;

	float tilt;
	float min_tilt;
	float max_tilt;

	float side;
	float min_side;
	float max_side;

	float pon;
	float min_pon;
	float max_pon;

	//Errors
	float tilt_error;
	float side_error;
	float pon_error;

	void initMessageKeepon(theatre_bot::KeeponMessage *message);

};

#endif /* KEEPONTORSO_H_ */
