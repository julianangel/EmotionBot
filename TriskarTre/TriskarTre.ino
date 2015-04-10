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
#include <theatre_bot/OdometryTriskar.h>
#include <theatre_bot/TriskarVelocity.h>
#include <theatre_bot/Twist32.h>
#include <theatre_bot/TriskarSmallUpper.h>


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
int time_PID = 25000;
unsigned short timer_PID = 25000;
unsigned long time_message = 50;
unsigned long time_message_upper = 500;
unsigned long last_message;
//Security Distance

/*Ros*/
ros::NodeHandle nh;
//Odometry, this one is a simplification which is ligher for arduino
theatre_bot::OdometryTriskar odometry_msg;
//Upper part message: x left servo, y central servo, and z right servo
theatre_bot::Vector32 uppper_msg;
/*
 * This function gets the velocity and set the points
 */
void messageCb(const theatre_bot::TriskarVelocity& msg);/*
 * x left servo
 * y center servo
 * z right servo
 */
//void servo_cb( const theatrebot_action_modulation::Vector32& cmd_msg);
void servo_cb( const theatre_bot::TriskarSmallUpper& cmd_msg);/*
 * Special commands to control the robot
 * Currently the commands are:
 *    -'R' = reset the info
 *    -'S' = stop the triskar
 */
void special_cb(const std_msgs::Char& special_cmd);
void stopRobot();
void timerHandler();


ros::Publisher odometryTriskar("odometry_triskar", &odometry_msg);
ros::Publisher upperPartTriskar("upper_triskar", &uppper_msg);

ros::Subscriber<theatre_bot::TriskarVelocity> setVelocity("vel_triskar",messageCb);
ros::Subscriber<theatre_bot::TriskarSmallUpper> setServo("servo_triskar", servo_cb);
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
  nh.advertise(upperPartTriskar); 
  //enable motors
  pinMode(enable_motors,OUTPUT);
  digitalWrite(enable_motors,HIGH);
  Timer6.attachInterrupt(timerHandler);
  Timer6.start(timer_PID); 
  robot.setPIDTime(time_PID);
  time_message = millis();
  time_message_upper = millis(); 
} 
 
void loop() 
{ 
 if ( (millis()-time_message) > 50){
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
       /*uppper_msg.x = robot.getUpperLeft();
       uppper_msg.y = robot.getUpperCenter();
       uppper_msg.z = robot.getUpperRight();
       upperPartTriskar.publish(&uppper_msg);*/
    time_message =  millis();
  }
  if((millis()-time_message_upper) > 100){
       uppper_msg.x = robot.getUpperLeft();
       uppper_msg.y = robot.getUpperCenter();
       uppper_msg.z = robot.getUpperRight();
       upperPartTriskar.publish(&uppper_msg);
    time_message_upper =  millis();
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
    robot.initUpperPart();
  }else if(special_cmd.data=='S'){
    robot.stop();    
  }

}

/*
 * This function gets the velocity and set the points
 */
void messageCb(const theatre_bot::TriskarVelocity& msg){
  last_message = millis();
  //if the robot is near to an object stops
  robot.setVelocity(static_cast<float>(msg.linear.x),static_cast<float>(msg.linear.y),static_cast<float>(msg.angular));
}

void servo_cb( const theatre_bot::TriskarSmallUpper& cmd_msg){
  if(cmd_msg.left_change){
    robot.writeUpperLeft(static_cast<int>(cmd_msg.left));
  }
  if(cmd_msg.center_change){
    robot.writeUpperCenter(static_cast<int>(cmd_msg.center));
  }
  if(cmd_msg.right_change){
    robot.writeUpperRight(static_cast<int>(cmd_msg.right));
  }
  //robot.writeUpperPart(static_cast<int>(cmd_msg.x),static_cast<int>(cmd_msg.y),static_cast<int>(cmd_msg.z));
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

