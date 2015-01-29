#include "DCMotor.h"

DCMotor::DCMotor(){
//PID
	PID_time = 0;
	outputMotorPID = 0.0;
	setPointMotor = 0.0;

}


void DCMotor::setDesirePoint(double point){
	setPointMotor = point;
}

void DCMotor::setAngularVelocityVariable(double *angular){
	angularVelocityMotor = angular;
}

float DCMotor::getDesireVelocity(){
	return static_cast<float>(outputMotorPID);
}
void DCMotor::PIDCompute(){
	motorPID.Compute();
}

void DCMotor::setInfoMotor(int d, int in1, int in2){
	m.setInfo(d,in1,in2);
}

void DCMotor::setPIDTime(int time){
	PID_time = time;
	motorPID.SetSampleTime(PID_time);
}



MC33887 * DCMotor::getMotor(){
	return &m;
}

void DCMotor::initPID(){
	*angularVelocityMotor = 0.0;
	outputMotorPID = 0.0;
	setPointMotor = 0.0;
	/*PID*/
	//Motor 1
	motorPID.setupPID(angularVelocityMotor, &outputMotorPID, &setPointMotor,5,1,0.0000001, DIRECT);
	motorPID.SetOutputLimits(-35,35);
	motorPID.SetMode(AUTOMATIC);
	motorPID.SetSampleTime(PID_time);

}
