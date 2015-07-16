#include "TheatrePlatform.h"

TheatrePlatform::TheatrePlatform(){
	motor_1.setInfoMotor(9, 50, 24);//(pwd, en1, en2)
	motor_2.setInfoMotor(10, 51, 25);//(pwd, en1, en2)
	motor_3.setInfoMotor(11, 22, 23);//(pwd, en1, en2)
	set_point_m1 = 0.0;
	set_point_m2 = 0.0;
	set_point_m3 = 0.0;
	triskar.setMotors(motor_1.getMotor(), motor_2.getMotor(), motor_3.getMotor());	
}


void TheatrePlatform::stop(){
    triskar.run(0.0, 0.0, 0.0);
    set_point_m1 = static_cast<double>(triskar.getM1());
    set_point_m2 = static_cast<double>(triskar.getM2());
    set_point_m3 = static_cast<double>(triskar.getM3());
    motor_1.setDesirePoint(set_point_m1);
    motor_2.setDesirePoint(set_point_m2);
    motor_3.setDesirePoint(set_point_m3);
    motor_1.PIDCompute();
    motor_2.PIDCompute();
    motor_3.PIDCompute();		
}


void TheatrePlatform::run(float velX, float velY, float velTheta){
    triskar.run(velX, velY, velTheta);
    set_point_m1 = static_cast<double>(triskar.getM1());
    set_point_m2 = static_cast<double>(triskar.getM2());
    set_point_m3 = static_cast<double>(triskar.getM3());
    motor_1.setDesirePoint(set_point_m1);
    motor_2.setDesirePoint(set_point_m2);
    motor_3.setDesirePoint(set_point_m3);
}

void TheatrePlatform::setPIDTuning(float p, float i, float d){
	motor_1.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
	motor_2.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
	motor_3.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
}

void TheatrePlatform::setPIDTuningMotor1(float p, float i, float d){
	motor_1.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
}

void TheatrePlatform::setPIDTuningMotor2(float p, float i, float d){
	motor_2.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
}
void TheatrePlatform::setPIDTuningMotor3(float p, float i, float d){
	motor_3.setPIDTuning(static_cast<double>(p),static_cast<double>(i),static_cast<double>(d));
}

void TheatrePlatform::PIDCompute(){
	motor_1.PIDCompute();
	motor_2.PIDCompute();
	motor_3.PIDCompute();	
	triskar.runM(motor_1.getDesireVelocity(),
          motor_2.getDesireVelocity(),
          motor_3.getDesireVelocity());
}

void TheatrePlatform::initPID(){
	motor_1.initPID();
	motor_2.initPID();
	motor_3.initPID();

}	
void TheatrePlatform::setInfoMotor1(int d, int in1, int in2)//(pwd, en1, en2)
{
	motor_1.setInfoMotor(d,in1,in2);
}

void TheatrePlatform::setInfoMotor2(int d, int in1, int in2)//(pwd, en1, en2)
{
	motor_2.setInfoMotor(d,in1,in2);
}

void TheatrePlatform::setInfoMotor3(int d, int in1, int in2)//(pwd, en1, en2)
{
	motor_3.setInfoMotor(d,in1,in2);
}

void TheatrePlatform::setPIDTime(int time){
	motor_1.setPIDTime(time);
	motor_2.setPIDTime(time);
	motor_3.setPIDTime(time);
}

MC33887 * TheatrePlatform::getMotor1(){
	return motor_1.getMotor();
}
MC33887 * TheatrePlatform::getMotor2(){
	return motor_2.getMotor();
}
MC33887 * TheatrePlatform::getMotor3(){
	return motor_3.getMotor();
}

void TheatrePlatform::setAngularVelocityVariable(double *angular1,double *angular2,double *angular3){
	motor_1.setAngularVelocityVariable(angular1);
	motor_2.setAngularVelocityVariable(angular2);
	motor_3.setAngularVelocityVariable(angular3);
}

float TheatrePlatform::getSetVelocityM1(){return triskar.getM1();}
float TheatrePlatform::getSetVelocityM2(){return triskar.getM2();}
float TheatrePlatform::getSetVelocityM3(){return triskar.getM3();}
float TheatrePlatform::getDesireVelocityM1(){
	return motor_1.getDesireVelocity();
	//return triskar.getM1();
}
float TheatrePlatform::getDesireVelocityM2(){
	return motor_2.getDesireVelocity();
	//return triskar.getM2();
}
float TheatrePlatform::getDesireVelocityM3(){
	return motor_3.getDesireVelocity();
	//return triskar.getM3();
}

