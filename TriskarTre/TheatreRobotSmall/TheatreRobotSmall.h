/*
 * TheatreRobotSmall.h
 *
 *  Created on: Oct 9, 2014
 *      Author: julian
 */

#ifndef ThreatreRobotSmall_H_
#define ThreatreRobotSmall_H_
#include "Arduino.h"

#include "TheatreUpperPart.h"

#include "TheatrePlatform.h"

//Triskar max and min velocity
#define MAX_VEL 1300.0f
#define MIN_VEL -1300.0f
#define MAX_VEL_ANGULAR 3.5f
#define MIN_VEL_ANGULAR -3.5f
#define MAX_TORSO_PART 90
#define MIN_TORSO_PART 10

class TheatreRobotSmall {
public:
	TheatreRobotSmall();
	void updatePosition(int count_motor_1,int count_motor_2,int count_motor_3);
	//Get
	float getPositionX();
	float getPositionY();
	float getPositionTheta();
	float getVelocityX();
	float getVelocityY();
	float getVelocityTheta();
	float getDesireVelocityM1();
	float getDesireVelocityM2();
	float getDesireVelocityM3();
	float getVelocityM1();
	float getVelocityM2();
	float getVelocityM3();
	//Set
	void setPositionX(float x);
	void setPositionY(float y);
	void setPositionTheta(float theta);
	void setPIDTime(int time);
	void setVelocity(float velX,float velY,float velTheta);
	void setPosition(float posX,float posY,float posTheta);
	void writeUpperPart(int left, int center, int right);
	void stop();
	void run();
private:
	TheatrePlatform platform;
	TheatreUpperPart upper_part;
	void initPID();
	int PID_time;
/*12V brushed DC motor with a 29:1 metal gearbox and an integrated quadrature encoder that provides a resolution of 64 counts per revolution of the motor shaft, which corresponds to 1856 counts per revolution of the gearbox�s output shaft.*/
	float countsMotor;
//Robot characteristics
	double timeSecond;
	double radio;//millimeters
	double factorDistance;
	double factorAngular;
//Movement
	bool isStop;
/*Robot Position*/
	double positionX;
	double positionY;
	double positionXTem;
	double positionYTem;
	double positionTheta;

/*Robot Velocity*/
	double velocityX;
	double velocityY;
	double velocityXTem ;
	double velocityYTem  ;
	double velocityTheta ;
	double t_count_motor_1;
	double t_count_motor_2;
	double t_count_motor_3;
	double angularVelocityMotor1;
	double angularVelocityMotor2;
	double angularVelocityMotor3;
};

#endif /* THEATREROBOTSMALL_H_ */
