/*
 * AbstractPlatformExecution.h
 *
 *  Created on: Jul 8, 2014
 *      Author: julian
 */

#ifndef ABSTRACTPLATFORMEXECUTION_H_
#define ABSTRACTPLATFORMEXECUTION_H_

#include "ros/ros.h"
/*
 * Each simple action must be implemented here.
 * if the action is not possible to be executed, it should return null
 */
class AbstractPlatformExecution {
public:
	AbstractPlatformExecution();
	virtual ~AbstractPlatformExecution()=0;

};

#endif /* ABSTRACTPLATFORMEXECUTION_H_ */
