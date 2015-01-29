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
	this->initPID();
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
	  platform.PIDCompute();
        }
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
	PID_time = static_cast<int>(time>>4);
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
