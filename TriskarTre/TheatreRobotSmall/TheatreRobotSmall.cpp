/*
 * TheatreRobotSmall.cpp
 *
 *  Created on: Oct 9, 2014
 *      Author: julian
 */

#include "TheatreRobotSmall.h"

TheatreRobotSmall::TheatreRobotSmall() {
/*12V brushed DC motor with a 29:1 metal gearbox and an integrated quadrature encoder that provides a resolution of 64 counts per revolution of the motor shaft, which corresponds to 1856 counts per revolution of the gearbox�s output shaft.*/
	countsMotor = 1920.0;
	radio = 35.0;
/*Robot position*/
	positionX     = 0.0;
	positionY     = 0.0;
	positionXTem  = 0.0;
	positionYTem  = 0.0;
	positionTheta = 0.0;
/*Robot Velocity*/
	velocityX     = 0;
	velocityY     = 0;
	velocityXTem  = 0.0;
	velocityYTem  = 0.0;
	velocityTheta = 0.0;
	angularVelocityMotor1 = 0.0;
	angularVelocityMotor2 = 0.0;
	angularVelocityMotor3 = 0.0;
	timeSecond = 0.0; 
	factorDistance = static_cast<double>(2.0*PI/countsMotor);
	factorAngular = static_cast<double>(2.0*PI/countsMotor/timeSecond);
	isStop = true;
	PID_time = 0.0;
	t_count_motor_1 = 0;
	t_count_motor_2 = 0;
	t_count_motor_3 = 0;
	this->initPID();
}

void TheatreRobotSmall::MoveBodyAction(float position_x,float position_y, float position_theta){
	isStop = false;
	body_controller.MoveBodyAction(position_x,position_y,position_theta);
}

void TheatreRobotSmall::OscillateBodyAction(float yaw){
	isStop = false;
	body_controller.OscillateBodyAction(yaw);
}

void TheatreRobotSmall::initUpperPart(){
	upper_part.initServo();	
}

float TheatreRobotSmall::getUpperLeft(){
	return static_cast<float>(upper_part.getLeft());
}

float TheatreRobotSmall::getUpperCenter(){
	return static_cast<float>(upper_part.getCenter());
}

float TheatreRobotSmall::getUpperRight(){
	return static_cast<float>(upper_part.getRight());
}


void TheatreRobotSmall::writeUpperLeft(int left){
	upper_part.setLeft(left);
}

void TheatreRobotSmall::writeUpperCenter(int center){
	upper_part.setCenter(center);
}
void TheatreRobotSmall::writeUpperRight(int right){
	upper_part.setRight(right);
}

void TheatreRobotSmall::writeUpperPart(int left, int center, int right){
	//upper_part.attach();
	if(center>MAX_TORSO_PART){
		center = MAX_TORSO_PART;
	}
	if(center<MIN_TORSO_PART){
		center = MIN_TORSO_PART;	
	}
	upper_part.write(left,center,right);
}


void TheatreRobotSmall::setPosition(float posX,float posY,float posTheta){
	positionX = posX;
	positionY = posY;
	positionTheta = posTheta;
}

void TheatreRobotSmall::updatePosition(int count_motor_1,int count_motor_2,int count_motor_3){
	angularVelocityMotor1 = static_cast<double>(count_motor_1);
	angularVelocityMotor2 = static_cast<double>(count_motor_2);
	angularVelocityMotor3 = static_cast<double>(count_motor_3);
	t_count_motor_1 = static_cast<double>(count_motor_1)*factorDistance;
	t_count_motor_2 = static_cast<double>(count_motor_2)*factorDistance;
	t_count_motor_3 = static_cast<double>(count_motor_3)*factorDistance;
	//Calculate angular velocity
	angularVelocityMotor1= angularVelocityMotor1*factorAngular;
	angularVelocityMotor2= angularVelocityMotor2*factorAngular; 
	angularVelocityMotor3= angularVelocityMotor3*factorAngular; 
        //Update tethe distance
	positionTheta	+= (-0.1061*t_count_motor_1-0.1061*t_count_motor_2-0.1061*t_count_motor_3);
	positionXTem		= (11.6667*t_count_motor_1+11.6667*t_count_motor_2-23.333*t_count_motor_3);
	positionYTem		= (-20.2073*t_count_motor_1+20.2073*t_count_motor_2);
        positionX       += positionXTem*cos(positionTheta)-positionYTem*sin(positionTheta);
        positionY       += positionXTem*sin(positionTheta)+positionYTem*cos(positionTheta);
        //Update the velocity
	velocityXTem	= (11.6667*angularVelocityMotor1+11.6667*angularVelocityMotor2-23.333*angularVelocityMotor3);
	velocityYTem	= (-20.2073*angularVelocityMotor1+20.2073*angularVelocityMotor2);
        velocityX       =velocityXTem*cos(positionTheta)-velocityYTem*sin(positionTheta);
        velocityY       =velocityXTem*sin(positionTheta)+velocityYTem*cos(positionTheta);
	velocityTheta	= -0.1061*angularVelocityMotor1-0.1061*angularVelocityMotor2-0.1061*angularVelocityMotor3;
        if(positionTheta>PI){
          positionTheta = positionTheta-2.0*PI;
        }else if(positionTheta<-PI){
          positionTheta = positionTheta+2.0*PI;
        }
	//PID
        if(!isStop){
        	if(body_controller.controll(static_cast<float>(positionX),static_cast<float>(positionY),static_cast<float>(positionTheta))){
			isStop = true;
			body_controller.stopMoveBodyAction();
			platform.stop();
		}else{
	        	platform.run(body_controller.getDesireVelocityX(), body_controller.getDesireVelocityY(), body_controller.getDesireVelocityTheta());
	        	platform.PIDCompute();
		}
        }
}

void TheatreRobotSmall::setNormalVelocity(float linear, float angular){
	body_controller.setVelocity(linear,angular);
}
void TheatreRobotSmall::setEmotionalMoveBody(bool repeat, int quantity, float distance[15],float velocity[15]){
	body_controller.setEmotionalMoveBody(repeat,quantity,distance,velocity);
}

void TheatreRobotSmall::synchEmotionMove(){
	body_controller.synchEmotionMove();
}

void TheatreRobotSmall::synchEmotionOscillate(){
	body_controller.synchEmotionOscillate();
}

void TheatreRobotSmall::setEmotionalOscillateBody(bool repeat, int quantity, float distance[15],float velocity[15]){
	body_controller.setEmotionalOscillateBody(repeat,quantity,distance,velocity);
}

bool TheatreRobotSmall::moveIsFinish(){
	bool temp = body_controller.getHasArrive();
	if(temp)
		body_controller.stopMoveBodyAction();
	return temp;
}

void TheatreRobotSmall::setPIDTuning(float p, float i, float d){
	platform.setPIDTuning(p,i,d);
} 

void TheatreRobotSmall::setPIDTuningMotor1(float p, float i, float d){
	platform.setPIDTuningMotor1(p,i,d);
}

void TheatreRobotSmall::setPIDTuningMotor2(float p, float i, float d){
	platform.setPIDTuningMotor2(p,i,d);
}

void TheatreRobotSmall::setPIDTuningMotor3(float p, float i, float d){
	platform.setPIDTuningMotor3(p,i,d);
}

//get
float TheatreRobotSmall::getPositionX(){
	return static_cast<float>(positionX);
}
float TheatreRobotSmall::getPositionY(){
	return static_cast<float>(positionY);
}
float TheatreRobotSmall::getPositionTheta(){
	return static_cast<float>(positionTheta);
}
float TheatreRobotSmall::getVelocityX(){
	return static_cast<float>(velocityX);
}
float TheatreRobotSmall::getVelocityY(){
	return static_cast<float>(velocityY);
}
float TheatreRobotSmall::getVelocityTheta(){
	return static_cast<float>(velocityTheta);
}
//Set
void TheatreRobotSmall::setPositionX(float x){positionX=x;}

void TheatreRobotSmall::setPositionY(float y){positionY=y;}

void TheatreRobotSmall::setPositionTheta(float theta){positionTheta=theta;}

void TheatreRobotSmall::setPIDTime(int time){
	PID_time = static_cast<int>(time/10000.0);
	timeSecond = static_cast<double>(time)/1000000.0;
	factorAngular = static_cast<double>(2.0*PI/countsMotor/timeSecond);
	platform.setPIDTime(PID_time);
}


void TheatreRobotSmall::setVelocity(float velX,float velY,float velTheta){
	isStop = false;
	//This protects that the velocity is out of bounds
    if(velX > MAX_VEL){
      velX = MAX_VEL;
    } else if(velX < MIN_VEL){
      velX = MIN_VEL;
    }
    if(velY > MAX_VEL){
	velY = MAX_VEL;
    } else if(velY < MIN_VEL){
      velY = MIN_VEL;
    }
    if(velTheta> MAX_VEL_ANGULAR){
	velTheta = MAX_VEL_ANGULAR;
   } else if(velTheta < MIN_VEL_ANGULAR){
	  velTheta = MIN_VEL_ANGULAR;
   }
   platform.run(velX, velY, velTheta);

}

void TheatreRobotSmall::stop(){
	isStop = true;
	//upper_part.detach();
	platform.stop();
	body_controller.stopMoveBodyAction();
	body_controller.stopOscillateBodyAction();
}

void TheatreRobotSmall::stopOscillateBody(){
	body_controller.stopOscillateBodyAction();
}

void TheatreRobotSmall::stopMoveBody(){
	body_controller.stopMoveBodyAction();
}

bool TheatreRobotSmall::moveEmotionSynch(){
	bool temp = body_controller.getEmotionalSynch();
	if(temp)
		body_controller.setEmotionalSynch(false);
	return temp;
}

void TheatreRobotSmall::run(){
	isStop = false;
}

float TheatreRobotSmall::getVelocityM1(){
   return static_cast<float>(angularVelocityMotor1);
}

float TheatreRobotSmall::getVelocityM2(){
   return static_cast<float>(angularVelocityMotor2);
}

float TheatreRobotSmall::getVelocityM3(){
   return static_cast<float>(angularVelocityMotor3);
}
void TheatreRobotSmall::initPID(){
	platform.setAngularVelocityVariable(&angularVelocityMotor1,&angularVelocityMotor2,&angularVelocityMotor3);
	platform.initPID();
}

float TheatreRobotSmall::getDesireVelocityM1(){
	return platform.getDesireVelocityM1();
}
float TheatreRobotSmall::getDesireVelocityM2(){
	return platform.getDesireVelocityM2();
}
float TheatreRobotSmall::getDesireVelocityM3(){
	return platform.getDesireVelocityM3();
}
float TheatreRobotSmall::getSetVelocityM1(){return platform.getSetVelocityM1();}
float TheatreRobotSmall::getSetVelocityM2(){return platform.getSetVelocityM2();}
float TheatreRobotSmall::getSetVelocityM3(){return platform.getSetVelocityM3();}

