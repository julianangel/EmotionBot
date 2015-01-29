/*
* This is the program could be used to controll a three wheel robot in a delta configuration and three servo motors. 
* It could be controlled:
*  - Velocity of each motor
*      it includes a pid for each motor (this should be tune)
*  - Three servo motors
* The information that it returns:
*    - Infrared
* Things to do or improve:
*   - Angle PID
*/


#define MAX_VEL 1300.0f
#define MIN_VEL -1300.0f
#define MAX_VEL_ANGULAR 3.5f
#define MIN_VEL_ANGULAR -3.5f

//This get faster the info from the pins
#include <digitalWriteFast.h>
//Need it to calculate velocity each x time
#include <TimerOne.h>
//PID
#include <PID_v1.h>
//Triskar libraries
#include <string.h>
#include <Triskar.h>
#include <MC33887.h>
//Servo motors
#include <Servo.h>
#include <SerialCommand.h>
//This libraries are for arduino communication
//This libraries are for sensor information
//Robot position


/*Velocity*/
/*12V brushed DC motor with a 29:1 metal gearbox and an integrated quadrature encoder that provides a resolution of 64 counts per revolution of the motor shaft, which corresponds to 1856 counts per revolution of the gearbox�s output shaft.*/
const float countsMotor = 1856.0;
//it is diveded by 2 because is just getting the upper part
const double countsCode = (double)countsMotor/2.0;
// set a timer of length 25000 microseconds (or 0.025 sec - or 40Hz )
const float timeCalculation = 25000.0;
const int timePID=(int) timeCalculation/10000.0;
const double timeSecond = (double)timeCalculation/1000000.0;//second
const double radio = 35.0;//millimeters
const double factorDistance = (double)2.0*PI/countsCode;
const float factorAngular = 2.0*PI/countsCode/timeSecond;
double distanceMotor1 = 0.0;
double distanceMotor1T = 0.0;
double distanceMotor2 = 0.0;
double distanceMotor2T = 0.0;
double distanceMotor3 = 0.0;
double distanceMotor3T = 0.0;
double angularVelocityMotor1 = 0.0;
double angularVelocityMotor2 = 0.0;
double angularVelocityMotor3 = 0.0;
double velocityMotor1 = 0.0;
double velocityMotor2 = 0.0;
double velocityMotor3 = 0.0;
double outputMotor1PID = 0.0;
double outputMotor2PID = 0.0;
double outputMotor3PID = 0.0;
double setPointMotor1 = 0.0;
double setPointMotor2 = 0.0;
double setPointMotor3 = 0.0;

/*Robot Position*/
double positionX     = 0.0;
double positionY     = 0.0;
double positionXTem  = 0.0;
double positionYTem  = 0.0;
double positionTheta = 0.0;

/*Robot Velocity*/
double velocityX     = 0.0;
double velocityY     = 0.0;
double velocityXTem  = 0.0;
double velocityYTem  = 0.0;
double velocityTheta = 0.0;

/*PID motors*/
PID motor1PID;
PID motor2PID;
PID motor3PID;
/*Motor 1*/
//Definition of the pins which handles the interruptions
#define motor1EncoderIsReversed
#define motor1_InterruptA 0 //2
#define motor1_PinA 2
#define motor1_InterruptB 1 //3
#define motor1_PinB 3
volatile bool motor1EncoderSetA;
volatile bool motor1EncoderSetB;
volatile long motor1EncoderTicks = 0L;

/*Motor 2*/
//Definition of the pins which handles the interruptions
#define motor2EncoderIsReversed
#define motor2_InterruptA 2//21
#define motor2_PinA 21
#define motor2_InterruptB 3//20
#define motor2_PinB 20
volatile bool motor2EncoderSetA;
volatile bool motor2EncoderSetB;
volatile long motor2EncoderTicks = 0L;


/*Motor 3*/
//Definition of the pins which handles the interruptions
#define motor3EncoderIsReversed
#define motor3_InterruptA 4//19
#define motor3_PinA 19
#define motor3_InterruptB 5//18
#define motor3_PinB 18
volatile bool motor3EncoderSetA;
volatile bool motor3EncoderSetB;
volatile long motor3EncoderTicks = 0L;

/*Servo Motors*/
Servo leftServo;//pin 4
Servo centralServo;//pin 5
Servo rightServo;//pin 6

/*Triskar*/
MC33887 m1(8, 22, 23);//(pwd, en1, en2)
MC33887 m2(9, 24, 25);//(pwd, en1, en2)
MC33887 m3(10, 26, 27);//(pwd, en1, en2)
Triskar triskar(m1, m2, m3);

bool isStop = true;

float velX=0, velY=0, velTheta=0;


const int analog_pin = 0;
unsigned long time_send_message;
unsigned long last_message;

/*Serial Command*/
SerialCommand sCmd;
float setpoint[3] = {0.0, 0.0, 0.0}; // setpoint[strafe, forward, angular]
int setPointServo[3] = {45,45,45}; //setPointServo[left, center, right] 
/*
* getRange() - samples the analog input from the ranger
* and converts it into meters.  
*/
float getRange(int pin_num){
	float sample;
	// Get data
	sample = analogRead(pin_num)*0.0048828125;
	// if the ADC reading is too low, 
	//   then we are really far away from anything
	float distance = 65.0*pow(sample, -1.10); 
	return distance; //convert to meters
}




unsigned long time = 0L;

void setup()
{
	/*Serial*/
	Serial.begin(115200);

	/* Setup callbacks for SerialCommand commands*/
	//Move the platform. it gets the x, y and theta velocities
	sCmd.addCommand("m", run_cb);
	//stop the platform
	sCmd.addCommand("s", stop_cb);
	//Move the servo motors. it gets for the three motors
	sCmd.addCommand("b", servo_cb);
	//Reset the values
	sCmd.addCommand("r", reset_cb);
	sCmd.setDefaultHandler(invalid);      


	//position   
	velX=0;
	velY=0;
	velTheta=0;
	/*PID*/
	//Motor 1
	motor1PID.setupPID(&angularVelocityMotor1, &outputMotor1PID, &setPointMotor1,5,1,0.0000001, DIRECT);
	motor1PID.SetOutputLimits(-35,35);
	motor1PID.SetMode(AUTOMATIC);
	motor1PID.SetSampleTime(timePID);
	//Motor 2
	motor2PID.setupPID(&angularVelocityMotor2, &outputMotor2PID, &setPointMotor2,5,1,0.0000001, DIRECT);
	motor2PID.SetOutputLimits(-35,35);
	motor2PID.SetMode(AUTOMATIC);
	motor2PID.SetSampleTime(timePID);
	//Motor 3
	motor3PID.setupPID(&angularVelocityMotor3, &outputMotor3PID, &setPointMotor3,5,1,0.0000001, DIRECT);
	motor3PID.SetOutputLimits(-35,35);
	motor3PID.SetMode(AUTOMATIC);
	motor3PID.SetSampleTime(timePID);
	/*Triskar*/
	triskar.stop();
	/*Timer Interrupt*/
	Timer1.initialize((long)timeCalculation);
	Timer1.attachInterrupt(calculateVelocityMotors);
	/*Quadrature encoders*/
	//Motor 1
	pinMode(motor1_PinA, INPUT);
	pinMode(motor1_PinB, INPUT);
	attachInterrupt(motor1_InterruptA, HandleMotor1InterruptA, RISING);
	attachInterrupt(motor1_InterruptB, HandleMotor1InterruptB, RISING);
	//Motor 2
	pinMode(motor2_PinA, INPUT);
	pinMode(motor2_PinB, INPUT);
	attachInterrupt(motor2_InterruptA, HandleMotor2InterruptA, RISING);
	attachInterrupt(motor2_InterruptB, HandleMotor2InterruptB, RISING);
	//Motor 1
	pinMode(motor3_PinA, INPUT);
	pinMode(motor3_PinB, INPUT);
	attachInterrupt(motor3_InterruptA, HandleMotor3InterruptA, RISING);
	attachInterrupt(motor3_InterruptB, HandleMotor3InterruptB, RISING);

	/*Servo*/
	leftServo.attach(4);
	leftServo.write(45);
	centralServo.attach(5);
	centralServo.write(90);
	rightServo.attach(6);
	rightServo.write(45);

	/*Position*/
	positionX = 0.0;
	positionY = 0.0;
	positionTheta = 0.0;
	/*Velocity*/
	velocityX = 0.0;
	velocityY = 0.0;
	velocityTheta = 0.0;

	isStop = true;
	last_message = millis();
	time_send_message = millis();
}

void loop()
{

	sCmd.readSerial(); // We don't do much, just process serial commands
	// publish the range value every 100 milliseconds
	//   since it takes that long for the sensor to stabilize
	if ( (millis()-time_send_message) > 100){
                //Serial.print("n-i\n");
		//Position Info
		Serial.print("p*");
		Serial.print((int)positionX);
		Serial.print("*");
		Serial.print((int)positionY);
		Serial.print("*");
		Serial.print((int)positionTheta);
		Serial.print("*");
		//velocity messagepositionYpositionY
		Serial.print("v*");
		Serial.print((int)velocityX);
		Serial.print("*");
		Serial.print((int)velocityY);
		Serial.print("*");
		Serial.print((int)velocityTheta);
		Serial.print("*\n");
                //Serial.print("n-f\n");
		time_send_message =  millis();
	}
	//If the robot does not receive information stop
	if((millis()-last_message)>1500){
		stop_cb();
	}
}

/*
* This function gets the velocity and set the points
*/
void run_cb(){
	last_message = millis();

	for (int i = 0; i < 3; i++) {
		char *arg;
		arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
		if (arg != NULL) {    // As long as it existed, take it
			setpoint[i] = atof(arg);
		} else {
			setpoint[i] = 0;
		}
	}
	if(setpoint[0]==0 && setpoint[1] ==0 && setpoint[2] == 0){
		stop_cb();  
	}else{
		isStop = false;
		velX=(float)setpoint[0];
		velY=(float)setpoint[1];
		velTheta = (float)setpoint[2];
		//This protects that the velocity is out of bounds
		if(setpoint[0]> MAX_VEL){
			velX = MAX_VEL;
		} else if(setpoint[0] < MIN_VEL){
			velX = MIN_VEL;
		}
		if(setpoint[1] > MAX_VEL){
			velY = MAX_VEL;
		} else if(setpoint[1] < MIN_VEL){
			velY = MIN_VEL;
		}
		if(setpoint[2]> MAX_VEL_ANGULAR){
			velTheta = MAX_VEL_ANGULAR;
		} else if(setpoint[2] < MIN_VEL_ANGULAR){
			velTheta = MIN_VEL_ANGULAR;
		}
		triskar.run((float)velX, (float)velY, (float)velTheta);
		setPointMotor1=triskar.getM1();
		setPointMotor2=triskar.getM2();
		setPointMotor3=triskar.getM3();
	}
	//digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

/*
* x left servo
* y center servo
* z right servo
*/
void servo_cb(){  
	for (int i = 0; i < 3; i++) {
		char *arg;
		arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
		if (arg != NULL) {    // As long as it existed, take it
			setPointServo[i] = atoi(arg);
		} else {
			setPointServo[i] = 0;
		}
	}
	leftServo.write(setPointServo[0]);
	centralServo.write(setPointServo[1]);
	rightServo.write(setPointServo[2]);
}

void reset_cb(){
        Serial.println("reset");
	/*Position*/
	positionX = 0.0;
	positionY = 0.0;
	positionTheta = 0.0;
	/*Velocity*/
	velocityX = 0.0;
	velocityY = 0.0;
	velocityTheta = 0.0;
	leftServo.write(45);
	centralServo.write(45);
	rightServo.write(45);
	stop_cb();
}

void stop_cb() {
	triskar.run(0,0,0);
	triskar.stop();
	isStop = true;
	setPointMotor1=0.0;
	setPointMotor2=0.0;
	setPointMotor3=0.0;
}

void invalid(const char *command) {
	Serial.println("Invalid command");
}

/*Timer Function*/

void calculateVelocityMotors(){
	//Save the info and reset the counter
	distanceMotor1T=motor1EncoderTicks;
	motor1EncoderTicks=0;
	distanceMotor2T=motor2EncoderTicks;
	motor2EncoderTicks=0;
	distanceMotor3T=motor3EncoderTicks;
	motor3EncoderTicks=0;
	//Calculate distance
	angularVelocityMotor1 = distanceMotor1T;
	angularVelocityMotor2 = distanceMotor2T;
	angularVelocityMotor3 = distanceMotor3T;
	distanceMotor1T*=factorDistance;//millimeters
	distanceMotor2T*=factorDistance;
	distanceMotor3T*=factorDistance;
	//Calculate angular velocity
	angularVelocityMotor1= angularVelocityMotor1*factorAngular;
	angularVelocityMotor2= angularVelocityMotor2*factorAngular; 
	angularVelocityMotor3= angularVelocityMotor3*factorAngular; 
	//Update tethe distance
	positionTheta	+= (-0.1061*distanceMotor1T-0.1061*distanceMotor2T-0.1061*distanceMotor3T);
	positionXTem	= (11.6667*distanceMotor1T+11.6667*distanceMotor2T-23.333*distanceMotor3T);
	positionYTem	= (-20.2073*distanceMotor1T+20.2073*distanceMotor2T);
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
	/*if(!isStop){
		motor1PID.Compute();
		motor2PID.Compute();
		motor3PID.Compute();
		triskar.runM((float)outputMotor1PID,
			(float)outputMotor2PID,
			(float)outputMotor3PID);
	}*/
}

/*Quadrature functions*/
//Motor 1
void HandleMotor1InterruptA(){
	motor1EncoderSetB = digitalReadFast(motor1_PinB);
#ifdef motor1EncoderIsReversed
	motor1EncoderTicks -= motor1EncoderSetB?-1:+1;
#else
	motor1EncoderTicks += motor1EncoderSetB?-1:+1;
#endif
}

void HandleMotor1InterruptB(){
	motor1EncoderSetA = digitalReadFast(motor1_PinA);
#ifdef motor1EncoderIsReversed
	motor1EncoderTicks += motor1EncoderSetA?-1:+1;
#else
	motor1EncoderTicks -= motor1EncoderSetA?-1:+1;
#endif
}

//Motor 2
void HandleMotor2InterruptA(){
	motor2EncoderSetB = digitalReadFast(motor2_PinB);
#ifdef motor2EncoderIsReversed
	motor2EncoderTicks -= motor2EncoderSetB?-1:+1;
#else
	motor2EncoderTicks += motor2EncoderSetB?-1:+1;
#endif
}

void HandleMotor2InterruptB(){
	motor2EncoderSetA = digitalReadFast(motor2_PinA);
#ifdef motor2EncoderIsReversed
	motor2EncoderTicks += motor2EncoderSetA?-1:+1;
#else
	motor2EncoderTicks -= motor2EncoderSetA?-1:+1;
#endif
}

//Motor 3
void HandleMotor3InterruptA(){
	motor3EncoderSetB = digitalReadFast(motor3_PinB);
#ifdef motor3EncoderIsReversed
	motor3EncoderTicks -= motor3EncoderSetB?-1:+1;
#else
	motor3EncoderTicks += motor3EncoderSetB?-1:+1;
#endif
}

void HandleMotor3InterruptB(){
	motor3EncoderSetA = digitalReadFast(motor3_PinA);
#ifdef motor3EncoderIsReversed
	motor3EncoderTicks += motor3EncoderSetA?-1:+1;
#else
	motor3EncoderTicks -= motor3EncoderSetA?-1:+1;
#endif
}
