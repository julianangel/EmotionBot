/*
 * DCMotor.h
 *
 *  Created on: Oct 9, 2014
 *      Author: julian
 */

#ifndef DCMotor_H_
#define DCMotor_H_
//PID
#include "PID_v1.h"
#include "MC33887.h"

class DCMotor{
public:
	DCMotor();
	void setPIDTime(int time);
	void setInfoMotor(int d, int in1, int in2);//(pwd, en1, en2)
	void initPID();	
	MC33887 * getMotor();
	void setAngularVelocityVariable(double *angular);
	void PIDCompute();
	float getDesireVelocity();
	void setDesirePoint(double point);
private:
	int PID_time;
	PID motorPID;
	double *angularVelocityMotor;
	double outputMotorPID;
	double setPointMotor;
	MC33887 m;//(pwd, en1, en2)
};
#endif /* DCMotor_H_ */
