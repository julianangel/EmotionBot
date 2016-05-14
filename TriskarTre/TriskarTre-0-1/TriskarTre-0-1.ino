#include <DueTimer.h>
#include <Servo.h>
#include "Encoder.h"
#include "PID_v1.h"
#include "MC33887.h"
#include "Triskar.h"
#include "TheatreRobotSmall.h"
/*This code is to set the pid parameters*/
/*ROS Libraries*/
#include <ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Char.h>
//Robot messages
#include <theatre_bot/TriskarMessage.h>
#include <theatre_bot/TriskarMessageEmotion.h>
#include <theatre_bot/ActionExecutionMessage.h>
#include <theatre_bot/OdometryTriskar.h>
#include <theatre_bot/Twist32.h>
#include <theatre_bot/TriskarSmallUpper.h>

//Motor
Encoder motor_1(26,27);
Encoder motor_2(28,29);
Encoder motor_3(30,31);
int enable_motors = 52;
//Robot
TheatreRobotSmall robot;

//PID velocity
// set a timer of length 25000 microseconds (or 0.025 sec - or 40Hz )
// set a timer of length 20000 microseconds (or 0.02 sec - or 50Hz )
// set a timer of length 10000 microseconds (or 0.01 sec - or 100Hz )
// set a timer of length 8000 microseconds (or 0.008 sec - or 125Hz )
int time_PID = 20000;
unsigned short timer_PID = 20000;
unsigned long time_message = 50;
unsigned long time_message_synch = 500;
unsigned long last_message;

/*Ros*/
ros::NodeHandle nh;

/*
 * Special commands to control the robot
 * Currently the commands are:
 *    -'R' = reset the info
 *    -'S' = stop the triskar
 */
void special_cb(const std_msgs::Char& special_cmd);
void stopRobot();
void timerHandler();
/*
 * Ros variables
 */
 //Odometry, this one is a simplification which is ligher for arduino
theatre_bot::OdometryTriskar odometry_msg;
theatre_bot::ActionExecutionMessage emotional_synch_message;
theatre_bot::ActionExecutionMessage action_synch_message;
//Upper part message: x left servo, y central servo, and z right servo
theatre_bot::Vector32 uppper_msg;
/*
 * Ros functions
 *//*
 * x left servo
 * y center servo
 * z right servo
 */
//void servo_cb( const theatrebot_action_modulation::Vector32& cmd_msg);
void servo_cb( const theatre_bot::TriskarSmallUpper& cmd_msg);
void setActionTriskar(const theatre_bot::TriskarMessage& msg);
void setVelocityTriskar(const theatre_bot::TriskarMessage& msg);
void stopActionTriskar(const theatre_bot::TriskarMessageEmotion& msg);
void setPositionTriskar(const theatre_bot::OdometryTriskar& msg);
void odometryLandmarks(const theatre_bot::OdometryTriskar& msg);
/*
 * Publisher
 */
//TODO publish the odometry information
//Method that published synch of move body
//ros::Publisher emotionalSynch("emotional_move_synch", &emotional_synch_message);
//ros::Publisher actionSynch("action_move_synch", &action_synch_message);
ros::Publisher odometryTriskar("odometry_triskar", &odometry_msg);
ros::Publisher upperPartTriskar("upper_triskar", &uppper_msg);
/*
 * Subscribers
 */
ros::Subscriber<std_msgs::Char> specialCommands("commands_triskar", special_cb);
ros::Subscriber<theatre_bot::TriskarSmallUpper> setServo("servo_triskar", servo_cb);
/*
 * The comming part order are
 * 0 move_body
 * 1 oscillate_body
 */
//action triskar
ros::Subscriber<theatre_bot::TriskarMessage> setAction("action_triskar",setActionTriskar);
//velocity triskar, it changes the base velocity of the robot
ros::Subscriber<theatre_bot::TriskarMessage> setVelocity("velocity_triskar",setVelocityTriskar);
//TODO emotional triskar subscriber
ros::Subscriber<theatre_bot::TriskarMessageEmotion> stopAction("stop_act_triskar",stopActionTriskar);
ros::Subscriber<theatre_bot::OdometryTriskar> setPosition("set_position_triskar",setPositionTriskar);
ros::Subscriber<theatre_bot::OdometryTriskar> setLandmark("odometry_landmarks",odometryLandmarks);
//TODO subscribe to update position from filter

//The setup function is called once at startup of the sketch
void setup()
{
	nh.getHardware()->setBaud(115200);
	last_message = 0;
	nh.initNode();
	//Subscribe
	nh.subscribe(specialCommands); 
	nh.subscribe(setAction); 
	nh.subscribe(setVelocity); 
	nh.subscribe(stopAction); 
        nh.subscribe(setServo); 
        nh.subscribe(setPosition); 
        nh.subscribe(setLandmark);
	//Publish
        //nh.advertise(emotionalSynch);
        //nh.advertise(actionSynch);
        nh.advertise(odometryTriskar);
        nh.advertise(upperPartTriskar);
	//enable motors
	pinMode(enable_motors,OUTPUT);
	digitalWrite(enable_motors,HIGH);
	Timer6.attachInterrupt(timerHandler);
	Timer6.start(timer_PID); 
	robot.setPIDTime(time_PID);
	robot.setPIDTuningMotor1(5.42655,11.665,0.0);
	robot.setPIDTuningMotor2(4.6323,11.665,0.0);
	robot.setPIDTuningMotor3(5.56786,16.5,0.0);
	time_message = millis();
	time_message_synch = millis(); 
}
float tt;
// The loop function is called in an endless loop
void loop()
{
	if ( (millis()-time_message) > 100){
                  //Position Info
                 odometry_msg.pose.position.x = robot.getPositionX();
                 odometry_msg.pose.position.y = robot.getPositionY();
                 odometry_msg.pose.orientation =  robot.getPositionTheta();
                 //velocity message
                 odometry_msg.twist.linear.x = robot.getVelocityX();
                 odometry_msg.twist.linear.y = robot.getVelocityY();
                 odometry_msg.twist.angular = robot.getVelocityTheta();
                 odometry_msg.commands.linear.x = robot.getIdealVelocityX();
                 odometry_msg.commands.linear.y = robot.getIdealVelocityY();
                 odometry_msg.commands.angular = robot.getIdealVelocityYaw();
                 odometryTriskar.publish(&odometry_msg);
                uppper_msg.x = robot.getUpperLeft();
                uppper_msg.y = robot.getUpperCenter();
                uppper_msg.z = robot.getUpperRight();
                upperPartTriskar.publish(&uppper_msg);
                time_message =  millis();
	}
	//It sends messages for syns
	/*if(robot.moveEmotionSynch()){
		emotional_synch_message.coming_from = "move_body";
		emotional_synch_message.coming_to = "";
		emotional_synch_message.message = "emotion_synch";
		emotionalSynch.publish(&emotional_synch_message);
	}
	if(robot.moveIsFinish()){
		action_synch_message.coming_from = "move_body";
		action_synch_message.coming_to = "";
		action_synch_message.message = "action_finished";
		actionSynch.publish(&action_synch_message);
	}*/
	nh.spinOnce();
} 


void setActionTriskar(const theatre_bot::TriskarMessage& msg){
	/*
	 * 0 move_body
	 * 1 oscillate_body
	 */
	if(msg.coming_from == 0){
		robot.MoveBodyAction(msg.x,msg.y,msg.z);
	}else if(msg.coming_from == 1){
		robot.OscillateBodyAction(msg.z);
	}
}

void setVelocityTriskar(const theatre_bot::TriskarMessage& msg){
	/*
	 * 0 move_body
	 * 1 oscillate_body
	 */
	if(msg.coming_from == 0){
		robot.setNormalVelocity(msg.x,msg.y);
	}else if(msg.coming_from == 1){
                robot.setOscillateVelocity(msg.x);
        }
}

void stopActionTriskar(const theatre_bot::TriskarMessageEmotion& msg){
	/*
	 * 0 move_body
	 * 1 oscillate_body
	 */
        if(msg.coming_to == 0){
          /*if(msg.synch){
            robot.synchEmotionMove();
          }else*/
          if(msg.stop){
            robot.stopMoveBody();
          }
          /*else{
              float distance[15];
              float velocity[15];
              for(int i=0;i<msg.distance_length;++i){
                  distance[i] = msg.distance[i];
                  velocity[i] = msg.velocity[i];
              }
              robot.setEmotionalMoveBody(msg.repeat,msg.distance_length,distance,velocity);
          }*/
        }else if(msg.coming_to == 1){
          /*if(msg.synch){
            robot.synchEmotionOscillate();
          }
          else*/
          if(msg.stop){
            robot.stopOscillateBody();
          }
          /*else{
            //TODO pass parameters
              float distance[15];
              float velocity[15];
              for(int i=0;i<msg.distance_length;++i){
                  distance[i] = msg.distance[i];
                  velocity[i] = msg.velocity[i];
              }
              robot.setEmotionalOscillateBody(msg.repeat,msg.distance_length,distance,velocity);
          }*/
        }
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
    robot.setNormalVelocity(500.0,2.0);
    robot.initUpperPart();
  }else if(special_cmd.data=='S'){
    robot.stop();    
  }
}


void odometryLandmarks(const theatre_bot::OdometryTriskar& msg){
  robot.odometryLandmarkCorrection(msg.pose.position.x,msg.pose.position.y,msg.pose.orientation);
}

void setPositionTriskar(const theatre_bot::OdometryTriskar& msg){
  robot.setPosition(msg.pose.position.x,msg.pose.position.y,msg.pose.orientation);
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
