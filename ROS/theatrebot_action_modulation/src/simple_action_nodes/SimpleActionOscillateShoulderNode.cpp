/*
 * SimpleActionOscillateShoulderNode.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: julian
 */


#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "ros/ros.h"
#include "../instances/platform_profiles/PlatformTest1.h"
#include "theatrebot_action_modulation/ActionExecutionActionDescriptionMessage.h"
#include "theatrebot_action_modulation/EmotionParametersMessage.h"
#include "theatrebot_action_modulation/Vector32.h"
#include "theatrebot_action_modulation/OdometryTriskar.h"
#include "theatrebot_action_modulation/SyncActionMessage.h"
#include <math.h>
using std::string;
using std::vector;

#define MAX_ANGLE	0.78539816339744830962f //M_PI/4
#define MAX_ANGULAR_VELOCITY 	2.0f //rad/seg
#define MAX_LINEAR_VELOCITY 1200.0f //mm/seg
/*
 * This function gets the velocity of the platform, thus it could update the current velocity
 * Also gets the current distance
 */
void updateTriskarInformation(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg);
/*
 * TODO
 * It should be added the platform description to get the maximum angle, and maximum velocity
 * to calculate the velocity of the shoulder
 */
void executeActionShoulder(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
void executeActionShoulderMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
void executeActionTorso(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);
void executeActionTorsoMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg);

//TODO implement file parameters
void loadParameters(string file);
//TODO implement the platform information from file and change the platform description
void loadPlatformAction(string file);
void triskarControl(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg);
float signum(float num);
float fabs(float num);
void actionFinishSync(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg);
void calculateVelocityWithoutEmotion(float temp_next_step);
void calculateVelocityWithEmotion();
int current_position_emotion;
string desire_platform = "triskar_small";
//TODO this should be change to a more advance description to control difference in the platforms
map <string,string> simple_actions;
ros::Subscriber sub_platform;
ros::Publisher 	triskar;
//To receive information when other action has finished
ros::Subscriber sub_action_finish;

/*
 * x left servo
 * y center servo
 * z right servo
 */
theatrebot_action_modulation::Vector32 message_position_triskar;
theatrebot_action_modulation::Vector32 current_position_triskar;

theatrebot_action_modulation::Twist32 current_velocity;

vector<theatrebot_action_modulation::EmotionParametersMessage> information_emotion_to_perform;
vector<theatrebot_action_modulation::EmotionParametersMessage> information_emotion_to_perform_shoulder_move;

vector<theatrebot_action_modulation::EmotionParametersMessage> information_emotion_to_perform_torso_move;
vector<theatrebot_action_modulation::EmotionParametersMessage> information_emotion_to_perform_torso_oscillate;
float max_angle;
float angle_torso = static_cast<float>(40.0/180.0*M_PI);
float base_angle_shoulder_left;
float base_angle_shoulder_right;
float delta_time = 0.1; //milli seconds
float oscillate_shoulder_velocity = 0.0;
bool action_is_executing = false;
bool action_is_executing_move_shoulder = false;
bool action_is_executing_move_torso = false;
bool forward_direction = true;
bool is_emotional_action_oscillate_shoulder = false;
bool is_principal = false;

float const base_angle_torso = static_cast<float>(40.0/180.0*M_PI);
float const base_left_arm = M_PI_4;
float const base_right_arm = M_PI_4;

int main(int argc, char **argv){
	// Set up ROS.
	PlatformTest1 *platform_description = new PlatformTest1;
	simple_actions = platform_description->getPlatformAction(desire_platform);
	ros::init(argc, argv, "simple_action_oscillate_shoulder_node");
	ros::NodeHandle n("/action_modulation");
	//Load  information
	if(n.getParam("/action_modulation/platform",desire_platform)){
		simple_actions = platform_description->getPlatformAction(desire_platform);
	}
	//Subscribe to the action action execution
	ros::Subscriber sub_shoulder = n.subscribe("simple_action_oscillate_shoulder_node", 5, executeActionShoulder);
	ros::Subscriber sub_move_shoulder = n.subscribe("simple_action_move_shoulder_node", 5, executeActionShoulderMove);
	ros::Subscriber sub_move_torso = n.subscribe("simple_action_move_torso_node", 5, executeActionTorsoMove);
	ros::Subscriber sub_oscillate_torso  = n.subscribe("simple_action_oscillate_torso_node", 5, executeActionTorso);
	//Subscribe to the correct platform controller
	if(desire_platform == "triskar_small"){
		ROS_INFO("triskar_small");
		sub_platform = 	n.subscribe("odometry_triskar", 5, updateTriskarInformation);
		triskar =  n.advertise<theatrebot_action_modulation::Vector32>("servo_triskar",5);
		message_position_triskar.x = static_cast<float>(base_left_arm/M_PI*180.0);
		message_position_triskar.y = static_cast<float>(base_angle_torso/M_PI*180.0);
		message_position_triskar.z = static_cast<float>(base_right_arm/M_PI*180.0);
		angle_torso = base_angle_torso;
		base_angle_shoulder_left = base_left_arm;
		base_angle_shoulder_right = base_right_arm;
	}else if(desire_platform == "triskar_big"){
		//TODO implement the position subscriber
	}
	sub_action_finish = n.subscribe("action_execution_sync",5,actionFinishSync);
	triskar.publish(message_position_triskar);
	oscillate_shoulder_velocity = 0.0;
	ros::spin();
	return 0;
}

void actionFinishSync(const theatrebot_action_modulation::SyncActionMessage::ConstPtr& msg){
	//TODO evaluate if it is necessary to introduce the name of the action
	if(msg->type_message.data == "finish"){
		action_is_executing = false;
		action_is_executing_move_shoulder = false;
		action_is_executing_move_torso = false;
		message_position_triskar.x = static_cast<float>(base_left_arm/M_PI*180.0);
		angle_torso = base_angle_torso;
		message_position_triskar.y = angle_torso/M_PI*180.0;
		base_angle_shoulder_left = base_left_arm;
		base_angle_shoulder_right = base_right_arm;
		message_position_triskar.z = static_cast<float>(base_right_arm/M_PI*180.0);
		oscillate_shoulder_velocity = 0.0;
		triskar.publish(message_position_triskar);
	}else if(msg->type_message.data == "sync_emotion"){
		current_position_emotion++;
		if(current_position_emotion>= information_emotion_to_perform.size()){
			current_position_emotion = 0;
		}
	}
	if(msg->action_name.data=="not_do_anything"){
		if(msg->type_message.data =="stop"){
			action_is_executing = false;
			action_is_executing_move_shoulder = false;
			action_is_executing_move_torso = false;
			message_position_triskar.x = static_cast<float>(base_left_arm/M_PI*180.0);
			angle_torso = static_cast<float>(base_angle_torso/180.0*M_PI);
			message_position_triskar.y = angle_torso/M_PI*180.0;
			base_angle_shoulder_left = base_left_arm;
			base_angle_shoulder_right = base_right_arm;
			message_position_triskar.z = static_cast<float>(base_right_arm/M_PI*180.0);
			oscillate_shoulder_velocity = 0.0;
			triskar.publish(message_position_triskar);
		}
	}
}
void executeActionShoulderMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg){
	ROS_INFO("Execute action move shoulder [%f %f] [%f %f]", msg->desire_position.desire_position.position.x,
			msg->desire_position.desire_position.position.y,
			msg->trajectory_characteristic.trajectory_characteristic.linear.x,
			msg->trajectory_characteristic.trajectory_characteristic.linear.y);
	//TODO information_emotion_to_perform_shoulder_move
	information_emotion_to_perform_shoulder_move.clear();
		current_position_emotion = 0;
		//Each time that is change the action is set the neutral position
		if(desire_platform == "triskar_small"){
			base_angle_shoulder_left = base_left_arm+msg->desire_position.desire_position.position.x;
			base_angle_shoulder_right = base_right_arm+msg->desire_position.desire_position.position.y;
			angle_torso = base_angle_torso;
			current_position_triskar.x = base_angle_shoulder_left;
			current_position_triskar.y = angle_torso;
			current_position_triskar.z = base_angle_shoulder_right;
			message_position_triskar.x = static_cast<int>(base_angle_shoulder_left/M_PI*180.0);
			message_position_triskar.y = static_cast<int>(angle_torso/M_PI*180.0);
			message_position_triskar.z = static_cast<int>(base_angle_shoulder_right/M_PI*180.0);
		}if(msg->action_type.data == "emotional"){
			is_emotional_action_oscillate_shoulder = true;
			base_angle_shoulder_left = base_left_arm;
			base_angle_shoulder_right = base_right_arm;
			ROS_INFO("it is emotional move shoulder");
		}
		for(int i=0;i<msg->emotion_parameters.size();i++){
			theatrebot_action_modulation::EmotionParametersMessage temp_message;
			temp_message.spacing = msg->emotion_parameters[i].spacing;
			temp_message.timing  = msg->emotion_parameters[i].timing;
			information_emotion_to_perform_shoulder_move.push_back(temp_message);
		}
	action_is_executing_move_shoulder = true;

}
void executeActionTorso(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg){
	ROS_INFO("Execute action oscillate torso [%f %f] [%f %f]", msg->desire_position.desire_position.position.x,
			msg->desire_position.desire_position.position.y,
			msg->trajectory_characteristic.trajectory_characteristic.linear.x,
			msg->trajectory_characteristic.trajectory_characteristic.linear.y);


}
void executeActionTorsoMove(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg){
	ROS_INFO("Execute action move torso [%f %f] [%f %f]", msg->desire_position.desire_position.position.x,
			msg->desire_position.desire_position.position.y,
			msg->trajectory_characteristic.trajectory_characteristic.linear.x,
			msg->trajectory_characteristic.trajectory_characteristic.linear.y);
	information_emotion_to_perform_torso_move.clear();
		current_position_emotion = 0;
		//Each time that is change the action is set the neutral position

		if(desire_platform == "triskar_small"){
			angle_torso = base_angle_torso + msg->desire_position.desire_position.position.x;
			base_angle_shoulder_left = base_left_arm;
			base_angle_shoulder_right = base_right_arm;
			current_position_triskar.x = base_angle_shoulder_left;
			current_position_triskar.y = angle_torso;
			current_position_triskar.z = base_angle_shoulder_right;
			message_position_triskar.x = static_cast<int>(base_angle_shoulder_left/M_PI*180);
			message_position_triskar.y = static_cast<int>(angle_torso/M_PI*180);
			message_position_triskar.z = static_cast<int>(base_angle_shoulder_right/M_PI*180);
		}if(msg->action_type.data == "emotional"){
			is_emotional_action_oscillate_shoulder = true;
			angle_torso = base_angle_torso;
			ROS_INFO("it is emotional move torso");
		}
		for(int i=0;i<msg->emotion_parameters.size();i++){
			theatrebot_action_modulation::EmotionParametersMessage temp_message;
			temp_message.spacing = msg->emotion_parameters[i].spacing;
			temp_message.timing  = msg->emotion_parameters[i].timing;
			information_emotion_to_perform_torso_move.push_back(temp_message);
		}
		action_is_executing_move_torso = true;

}


//TODO add angle controller
void updateTriskarInformation(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg){
	//Suppose that each information is send every 100 milliseconds
	if(action_is_executing){
		//if(!is_emotional_action_oscillate_shoulder){
			/*
			 * Move shoulder
			 */
			float temp_velocity = sqrtf(powf(msg->twist.linear.x,2)+powf(msg->twist.linear.y,2));//mm/seg
			//Calculate the angular velocity
			float temp_angular_velocity = temp_velocity/MAX_LINEAR_VELOCITY*MAX_ANGULAR_VELOCITY;
			//Calculate next step from the velocity;
			float temp_next_step = temp_angular_velocity*delta_time;
			if(information_emotion_to_perform.size() == 0){
				if(oscillate_shoulder_velocity == 0){
					calculateVelocityWithoutEmotion(temp_next_step);
				}else{
					calculateVelocityWithoutEmotion(oscillate_shoulder_velocity*delta_time);
				}

			}else if(information_emotion_to_perform.size() >= 0){
				calculateVelocityWithEmotion();
			}
	}
	if(action_is_executing_move_shoulder){
		if(information_emotion_to_perform_shoulder_move.size() != 0){
			base_angle_shoulder_left = base_left_arm + information_emotion_to_perform_shoulder_move[current_position_emotion].spacing;
			base_angle_shoulder_right= base_right_arm -information_emotion_to_perform_shoulder_move[current_position_emotion].spacing;
		}
	}
	if(action_is_executing_move_torso){
		/*
		 * Move torso
		 */
		if(information_emotion_to_perform_torso_move.size() == 0){
			current_position_triskar.y = angle_torso;
			message_position_triskar.y = static_cast<int>(current_position_triskar.y/M_PI*180.0);
		}else if(information_emotion_to_perform_torso_move.size() != 0){
			current_position_triskar.y = angle_torso+information_emotion_to_perform_torso_move[current_position_emotion].spacing;
			message_position_triskar.y = static_cast<int>(current_position_triskar.y/M_PI*180.0);
		}
	}

	triskar.publish(message_position_triskar);
}

void calculateVelocityWithoutEmotion( float temp_next_step){
	if(forward_direction){
		current_position_triskar.x = current_position_triskar.x + temp_next_step;
		current_position_triskar.z = current_position_triskar.z + temp_next_step;
		if(current_position_triskar.x>=base_angle_shoulder_left+max_angle){
			forward_direction = !forward_direction;
			current_position_triskar.x = base_angle_shoulder_left+max_angle;
			current_position_triskar.z = base_angle_shoulder_right+max_angle;
		}
	}else if(!forward_direction){
		current_position_triskar.x = current_position_triskar.x - temp_next_step;
		current_position_triskar.z = current_position_triskar.z - temp_next_step;
		if(current_position_triskar.x<=base_angle_shoulder_left-max_angle){
			forward_direction = !forward_direction;
			current_position_triskar.x = base_angle_shoulder_left-max_angle;
			current_position_triskar.z = base_angle_shoulder_right-max_angle;
		}
	}
	//Get the int part of the calculation
	message_position_triskar.x = static_cast<int>(current_position_triskar.x/M_PI*180);
	message_position_triskar.z = static_cast<int>(current_position_triskar.z/M_PI*180);
	ROS_INFO("the angles are %f %f",message_position_triskar.x,message_position_triskar.z);
}

void calculateVelocityWithEmotion(){
	double emotion_velocity = information_emotion_to_perform[current_position_emotion].spacing/
			information_emotion_to_perform[current_position_emotion].timing;
	max_angle = information_emotion_to_perform[current_position_emotion].spacing;
	if(forward_direction){
			current_position_triskar.x = current_position_triskar.x + emotion_velocity*delta_time;
			current_position_triskar.z = current_position_triskar.z + emotion_velocity*delta_time;
			if(current_position_triskar.x>=base_angle_shoulder_left+max_angle){
				forward_direction = !forward_direction;
				current_position_triskar.x = base_angle_shoulder_left+max_angle;
				current_position_triskar.z = base_angle_shoulder_right+max_angle;
			}
		}else if(!forward_direction){
			current_position_triskar.x = current_position_triskar.x - emotion_velocity*delta_time;
			current_position_triskar.z = current_position_triskar.z - emotion_velocity*delta_time;
			if(current_position_triskar.x<=base_angle_shoulder_left-max_angle){
				forward_direction = !forward_direction;
				current_position_triskar.x = base_angle_shoulder_left-max_angle;
				current_position_triskar.z = base_angle_shoulder_right-max_angle;
			}
		}
		//Get the int part of the calculation
		message_position_triskar.x = static_cast<int>(current_position_triskar.x/M_PI*180);
		message_position_triskar.z = static_cast<int>(current_position_triskar.z/M_PI*180);
		ROS_INFO("the angles are %f %f, angle %f, f: %d, base: %f %f",
				message_position_triskar.x,message_position_triskar.z,
				max_angle,forward_direction,base_angle_shoulder_left,base_angle_shoulder_right);
}


void executeActionShoulder(const theatrebot_action_modulation::ActionExecutionActionDescriptionMessage::ConstPtr& msg)
{
	ROS_INFO("Execute action oscillate shoulder [%f %f] [%f %f]", msg->desire_position.desire_position.position.x,
			msg->desire_position.desire_position.position.y,
			msg->trajectory_characteristic.trajectory_characteristic.linear.x,
			msg->trajectory_characteristic.trajectory_characteristic.linear.y);
	information_emotion_to_perform.clear();
	current_position_emotion = 0;
	oscillate_shoulder_velocity = 0;
	//Each time that is change the action is set the neutral position
	if(desire_platform == "triskar_small"){
		base_angle_shoulder_left = base_left_arm;
		base_angle_shoulder_right = base_right_arm;
		current_position_triskar.x = base_angle_shoulder_left;
		current_position_triskar.y = angle_torso;
		current_position_triskar.z = base_angle_shoulder_right;
		message_position_triskar.x = static_cast<int>(base_angle_shoulder_left/M_PI*180);
		message_position_triskar.y = static_cast<int>(angle_torso/M_PI*180);
		message_position_triskar.z = static_cast<int>(base_angle_shoulder_right/M_PI*180);
	}
	oscillate_shoulder_velocity = msg->trajectory_characteristic.trajectory_characteristic.linear.x;
	if(msg->action_type.data == "mandatory"){
		if(msg->desire_position.desire_position.position.x<MAX_ANGLE){
			max_angle = msg->desire_position.desire_position.position.x;
		}else{
			max_angle = MAX_ANGLE;
		}
	}else if(msg->action_type.data == "emotional"){
		is_emotional_action_oscillate_shoulder = true;
		ROS_INFO("it is emotional oscillate shoulder");
	}
	for(int i=0;i<msg->emotion_parameters.size();i++){
		theatrebot_action_modulation::EmotionParametersMessage temp_message;
		temp_message.spacing = msg->emotion_parameters[i].spacing;
		temp_message.timing  = msg->emotion_parameters[i].timing;
		information_emotion_to_perform.push_back(temp_message);
	}
	action_is_executing = true;
	forward_direction = true;
}


void triskarControl(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg){
	//get speed
}

//TODO implement file parameters
void loadParameters(string file){

}
//TODO implement the platform information from file and change the platform description
void loadPlatformAction(string file){

}

float signum(float num){
	if(num<0)
		return -1;
	return 1;
}

float fabs(float num){
	if(num<0)
		return -1*num;
	return num;
}
