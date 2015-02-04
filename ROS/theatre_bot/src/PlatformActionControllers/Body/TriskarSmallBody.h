/*
 * TriskarSmallBody.h
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLBODY_H_
#define TRISKARSMALLBODY_H_

#include "BodyAction.h"

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
};

#endif /* TRISKARSMALLBODY_H_ */
