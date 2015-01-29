#include <DueTimer.h>
#include <Servo.h>
#include "Encoder.h"
#include "PID_v1.h"
#include "MC33887.h"
#include "Triskar.h"
#include "TheatreRobotSmall.h"

/*ROS Libraries*/
#include <ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Char.h>
//This libraries are for sensor information
#include <ros/time.h>
#include <sensor_msgs/Range.h>
//Robot position
#include <theatrebot_action_modulation/OdometryTriskar.h>
#include <theatrebot_action_modulation/TriskarVelocity.h>
#include <theatrebot_action_modulation/Twist32.h>

//Motor
Encoder motor_1(26,27);
Encoder motor_2(28,29);
Encoder motor_3(30,31);
int enable_motors = 52;
//int x,y,z;
//Robot
TheatreRobotSmall robot;

//PID velocity
// set a timer of length 25000 microseconds (or 0.025 sec - or 40Hz )
int time_PID = 20000;
unsigned short timer_PID = 20000;
unsigned long time_message = 100;
unsigned long last_message;
//Security Distance

/*Ros*/
ros::NodeHandle nh;
//Odometry, this one is a simplification which is ligher for arduino
theatrebot_action_modulation::OdometryTriskar odometry_msg;
/*
 * This function gets the velocity and set the points
 */
void messageCb(const theatrebot_action_modulation::TriskarVelocity& msg);/*
 * x left servo
 * y center servo
 * z right servo
 */
void servo_cb( const theatrebot_action_modulation::Vector32& cmd_msg);
void servo_cb( const theatrebot_action_modulation::Vector32& cmd_msg);/*
 * Special commands to control the robot
 * Currently the commands are:
 *    -'R' = reset the info
 *    -'S' = stop the triskar
 */
void special_cb(const std_msgs::Char& special_cmd);
void stopRobot();
void timerHandler();


ros::Publisher odometryTriskar("odometry_triskar", &odometry_msg);

ros::Subscriber<theatrebot_action_modulation::TriskarVelocity> setVelocity("vel_triskar",messageCb);
ros::Subscriber<theatrebot_action_modulation::Vector32> setServo("servo_triskar", servo_cb);
ros::Subscriber<std_msgs::Char> specialCommands("commands_triskar", special_cb);

void setup() 
{ 
  nh.getHardware()->setBaud(115200);
  last_message = 0;
  nh.initNode();
  nh.subscribe(setVelocity);
  nh.subscribe(setServo); 
  nh.subscribe(specialCommands); 
  nh.advertise(odometryTriskar); 
  //enable motors
  pinMode(enable_motors,OUTPUT);
  digitalWrite(enable_motors,HIGH);
  Timer6.attachInterrupt(timerHandler);
  Timer6.start(timer_PID); 
  robot.setPIDTime(time_PID);
  time_message = millis();
  
} 
 
void loop() 
{ 
 if ( (millis()-time_message) > 100){
    //Position Info
       odometry_msg.pose.position.x = robot.getPositionX();
       odometry_msg.pose.position.y = robot.getPositionY();
       odometry_msg.pose.orientation =  robot.getPositionTheta();
       /*odometry_msg.pose.position.x = x;
       odometry_msg.pose.position.y = y;
       odometry_msg.pose.orientation =  z;*/
       //velocity message
       odometry_msg.twist.linear.x = robot.getVelocityX();
       odometry_msg.twist.linear.y = robot.getVelocityY();
       odometry_msg.twist.angular = robot.getVelocityTheta();
       odometryTriskar.publish(&odometry_msg);
   
    time_message =  millis();
  }
     //If the robot does not receive information stop
  if((millis()-last_message)>1500){
    stopRobot();
  }
  nh.spinOnce();
} 
 
/*
 * Special commands to control the robot
 * Currently the commands are:
 *    -'R' = reset the info
 *    -'S' = stop the triskar
 */
void special_cb(const std_msgs::Char& special_cmd){
  if(special_cmd.data=='R'){
    robot.stop();
    robot.setVelocity(0.0,0.0,0.0);
    robot.setPosition(0.0,0.0,0.0);
    robot.writeUpperPart(45,40,45);
  }else if(special_cmd.data=='S'){
    robot.stop();    
  }

}

/*
 * This function gets the velocity and set the points
 */
void messageCb(const theatrebot_action_modulation::TriskarVelocity& msg){
  last_message = millis();
  //if the robot is near to an object stops
  robot.setVelocity(static_cast<float>(msg.linear.x),static_cast<float>(msg.linear.y),static_cast<float>(msg.angular));
}

void servo_cb( const theatrebot_action_modulation::Vector32& cmd_msg){
  robot.writeUpperPart(cmd_msg.x,cmd_msg.y,cmd_msg.z);
}

void stopRobot(){
  robot.stop();
}

void timerHandler(){
  int counter_motor_1 = motor_1.read();
  motor_1.write(0);
  int counter_motor_2 = motor_2.read();
  motor_2.write(0);
  int counter_motor_3 = motor_3.read();
  motor_3.write(0);
  robot.updatePosition(counter_motor_1,counter_motor_2,counter_motor_3);
}

