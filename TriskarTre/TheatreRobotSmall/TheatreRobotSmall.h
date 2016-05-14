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
#include "BodyController.h"

//Triskar max and min velocity
#define MAX_VEL 1250.0f
#define MIN_VEL -1250.0f
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
	float getUpperLeft();
	float getUpperCenter();
	float getUpperRight();
	float getSetVelocityM1();
	float getSetVelocityM2();
	float getSetVelocityM3();
	//Set
	void setPositionX(float x);
	void setPositionY(float y);
	void setPositionTheta(float theta);
	void setPIDTime(int time);
	void setVelocity(float velX,float velY,float velTheta);
	void setPosition(float posX,float posY,float posTheta);
	void writeUpperPart(int left, int center, int right);
	void initUpperPart();
	void writeUpperLeft(int left);
	void writeUpperCenter(int center);
	void writeUpperRight(int right);
	void setPIDTuning(float p, float i, float d); 
	void setPIDTuningMotor1(float p, float i, float d);
	void setPIDTuningMotor2(float p, float i, float d);
	void setPIDTuningMotor3(float p, float i, float d);
	void stop();
	void run();
	//
	void stopMoveBody();
	void stopOscillateBody();
	bool moveEmotionSynch();// it should set to this false after is read it
	bool moveIsFinish();
	//void setEmotionalMoveBody(bool repeat, int quantity, float distance[15],float velocity[15]);
	//void setEmotionalOscillateBody(bool repeat, int quantity, float distance[15],float velocity[15]);
	void setNormalVelocity(float linear, float angular);
	//void synchEmotionMove();
	//void synchEmotionOscillate();
	void setOscillateVelocity(float velocity_yaw);
	void odometryLandmarkCorrection(float position_x,float position_y,float position_yaw);
	//
	void MoveBodyAction(float position_x,float position_y, float position_theta);
	void OscillateBodyAction(float yaw);
	// Ideal velocities get
	float getIdealVelocityX();
	float getIdealVelocityY();
	float getIdealVelocityYaw();
private:
	TheatrePlatform platform;
	TheatreUpperPart upper_part;
	void initPID();
	void init_ideal_velocities();
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
/**Robot upper part/
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
/*Variables that are necessary for Kalman these are publish to be used. Every time that the information is get it to send, they are divided. While every time that new position is seted they become 0*/
	double ideal_velocity_counter;	
	double ideal_velocity_x;
	double ideal_velocity_y;
	double ideal_velocity_yaw;
	/*Robot body controller*/
	BodyController body_controller;
};

#endif /* THEATREROBOTSMALL_H_ */
