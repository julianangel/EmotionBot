/*
 * TheatrePlatform.h
 *
 *  Created on: Oct 9, 2014
 *      Author: julian
 */

#ifndef TheatrePlatform_H_
#define TheatrePlatform_H_

#include "DCMotor.h"
#include "Triskar.h"

class TheatrePlatform{
public:
	TheatrePlatform();
//set
	void setPIDTime(int time);
	void setInfoMotor1(int d, int in1, int in2);//(pwd, en1, en2)
	void setInfoMotor2(int d, int in1, int in2);//(pwd, en1, en2)
	void setInfoMotor3(int d, int in1, int in2);//(pwd, en1, en2)

	void setAngularVelocityVariable(double *angular1,double *angular2,double *angular3);
//Get
	MC33887 * getMotor1();
	MC33887 * getMotor2();
	MC33887 * getMotor3();
	float getDesireVelocityM1();
	float getDesireVelocityM2();
	float getDesireVelocityM3();
	void initPID();	
	void PIDCompute();
	void stop();
	void run(float velX, float velY, float velTheta);
private:
	DCMotor motor_1;
	DCMotor motor_2;
	DCMotor motor_3;
	Triskar triskar;
};
#endif /* TheatrePlatform_H_ */