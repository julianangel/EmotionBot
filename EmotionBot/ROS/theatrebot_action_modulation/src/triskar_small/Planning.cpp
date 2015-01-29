/*
 * Planning.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: julian
 */

#include "Planning.h"

Planning::Planning() {
	this->distance_travel = 0;
	this->temp_distance_traveled = 0;
	this->control_angle = true;
	this->has_arrived = false;
	maximum_error_x = 50.0;//in millimeters
	maximum_error_y = 50.0;//in millimeters
	maximum_error_theta = 0.07; //radians
	reduce_velocity_distance = 200.0; //in millimeters
	reduce_velocity_angular_distance = 0.2; //radians
	current_position_emotion = 0;
	forward_direction = true;
	delta_time = 0.1; //milli seconds
	is_emotional_action_oscillate = false;
}

Planning::~Planning() {
	// TODO Auto-generated destructor stub
}


theatrebot_action_modulation::TriskarVelocity Planning::calculateVelocity(
		const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
		theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed,
		ros::Publisher pub_action_finish){

	theatrebot_action_modulation::TriskarVelocity message;
	//Calculate the distance to the desire position
	float temp_current_distance =
			sqrt(
					pow(information_to_performed.desire_position.desire_position.position.x-msg->pose.position.x,2)
					+
					pow(information_to_performed.desire_position.desire_position.position.y-msg->pose.position.y,2));
	//Change in the reference frame
	float x_temp = information_to_performed.desire_position.desire_position.position.x-msg->pose.position.x;
	float y_temp = information_to_performed.desire_position.desire_position.position.y-msg->pose.position.y;
	float distance_x = cos(msg->pose.orientation)*x_temp+sin(msg->pose.orientation)*y_temp;
	float distance_y = cos(msg->pose.orientation)*y_temp-sin(msg->pose.orientation)*x_temp;
	float temp_angle_to_desire_position =
			atan2f(distance_y,
					distance_x);
	float temp_angle = msg->pose.orientation;
	float distance_theta = static_cast<float>(tf::getYaw(information_to_performed.desire_position.desire_position.orientation)-temp_angle);
	distance_theta = correctAngle(distance_theta);
	//ROS_INFO("size emotion parameters: %d",information_to_performed.emotion_parameters.size());
	if((information_to_performed.emotion_parameters.size() == 0)){
		calculateVelocityWithoutEmotion(msg,&message,distance_x,distance_y,distance_theta,information_to_performed);
	}
	//control if the action as emotion parameters
	else if (information_to_performed.emotion_parameters.size() > 0) {
		//ROS_INFO("Distance to angle: %f",distance_theta);
		this->calculateVelocityWithEmotion(msg,&message,distance_x,distance_y,distance_theta,temp_current_distance,
						temp_angle_to_desire_position,information_to_performed,pub_action_finish);
	}
	if(fabs(distance_theta)<maximum_error_theta&&control_angle){
		message.angular = 0.0;
	}
	if(fabs(distance_x)<maximum_error_x
			&&
			fabs(distance_y)<maximum_error_y&&(fabs(distance_theta)<maximum_error_theta||!control_angle)){
		this->has_arrived = true;
	}
	return message;
}


void Planning::calculateVelocityWithEmotion(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg
		,theatrebot_action_modulation::TriskarVelocity *message,
		float distance_x, float distance_y, float distance_theta, float temp_current_distance,
		float temp_angle_to_desire_position,
		theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed,
		ros::Publisher pub_action_finish){
	float aproach_velocity;
	float emotion_velocity;
	//TODO change to the last point, this will fix problems related to curve trajectories
	temp_distance_traveled +=
			sqrt(pow(msg->pose.position.x - initial_pose.position.x,2)
					+pow(msg->pose.position.y - initial_pose.position.y,2));
	//Check the distance
	if((temp_distance_traveled-distance_travel)>information_to_performed.emotion_parameters[current_position_emotion].spacing
	                                                            &&information_to_performed.action_is_principal.data){
		if(current_position_emotion<information_to_performed.emotion_parameters.size()-1){
			current_position_emotion++;
		}
		//Send sync message
		theatrebot_action_modulation::SyncActionMessage temp_message_finish;
		temp_message_finish.action_name.data = "move_body";
		temp_message_finish.type_message.data = "sync_emotion";
		temp_message_finish.action_success.data = true;
		pub_action_finish.publish(temp_message_finish);
	}
	/*if(current_position_emotion>=information_to_performed.emotion_parameters.size()){
		current_position_emotion = 0;
		distance_travel = temp_distance_traveled;
	}*/
	//spacing in mm and timing in milliseconds, the result is given in mm/s thus it should be converterd to mm/s
	emotion_velocity = (information_to_performed.emotion_parameters[current_position_emotion].spacing/
			information_to_performed.emotion_parameters[current_position_emotion].timing);
	//This case is just for velocity
	//x
	if(fabs(distance_x)<reduce_velocity_distance){
		float temp_vel =
				cos(temp_angle_to_desire_position)*
				emotion_velocity;
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x != 0){
			//TODO add the change function
		}else{
			aproach_velocity = temp_vel/reduce_velocity_distance;
		}
		message->linear.x = abs(aproach_velocity)*distance_x;
		//ROS_INFO("Emotional reduce x %f v: %f", temp_vel,emotion_velocity);
	}else{
		float temp_vel =
				cos(temp_angle_to_desire_position)*
				emotion_velocity;
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x != 0){
			//TODO add the change function
		}else{
			message->linear.x = temp_vel;
		}
		//ROS_INFO("Emotional x %f v: %f", temp_vel,emotion_velocity);

	}
	//Y
	if(fabs(distance_y)<reduce_velocity_distance){
		float temp_vel =
				sin(temp_angle_to_desire_position)*
				emotion_velocity;
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y != 0){
			//TODO add the change function
		}else{
			aproach_velocity = temp_vel/reduce_velocity_distance;
		}
		message->linear.y = abs(aproach_velocity)*distance_y;
		//ROS_INFO("Emotional reduce tem %f y %f", temp_vel,message->linear.y);
	}else{
		float temp_vel =
				sin(temp_angle_to_desire_position)*
				emotion_velocity;
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y != 0){
			//TODO add the change function
		}else{
			message->linear.y = temp_vel;
		}
		//ROS_INFO("Emotional tem %f y %f", temp_vel,message->linear.y);
	}
	if(control_angle){
		float temp_vel= emotion_velocity/MAX_LINEAR_VELOCITY*MAX_ANGULAR_VELOCITY;
		if(fabs(distance_theta)<reduce_velocity_angular_distance){
			if(information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x != 0){
				//TODO add the change function
			}else{
				aproach_velocity = temp_vel/reduce_velocity_angular_distance;
			}
			message->angular = aproach_velocity*distance_theta;
		}else{
			if(information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x != 0){
				//TODO add the change function
			}else{
				message->angular = temp_vel*signum(distance_theta);
			}
		}
	}
}

void Planning::calculateVelocityWithoutEmotion(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
		theatrebot_action_modulation::TriskarVelocity *message,
		float distance_x, float distance_y, float distance_theta,
		theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed){
	float aproach_velocity;
	//This case is just for velocity
	if(fabs(distance_x)<reduce_velocity_distance){
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x != 0){
			aproach_velocity = information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x/reduce_velocity_distance;
		}else{
			aproach_velocity = LINEAL_VELOCITY/reduce_velocity_distance;
		}
		message->linear.x = aproach_velocity*distance_x;
		//ROS_INFO("Reducing velocity_x: %f", message->linear.x);
	}else{
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x != 0){
			message->linear.x = information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.x*signum(distance_x);
		}else{
			message->linear.x = LINEAL_VELOCITY*signum(distance_x);
		}
	}
	if(fabs(distance_y)<reduce_velocity_distance){
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y != 0){
			aproach_velocity = information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y/reduce_velocity_distance;
		}else{
			aproach_velocity = LINEAL_VELOCITY/reduce_velocity_distance;
		}
		message->linear.y = aproach_velocity*distance_y;
		//ROS_INFO("Reducing velocity_y: %f", message->linear.y);
	}else{
		if(information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y != 0){
			message->linear.y = information_to_performed.trajectory_characteristic.trajectory_characteristic.linear.y*signum(distance_y);
		}else{
			message->linear.y = LINEAL_VELOCITY*signum(distance_y);
		}
	}
	if(control_angle){
		if(fabs(distance_theta)<reduce_velocity_angular_distance){
			if(information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x != 0){
				aproach_velocity = information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x/reduce_velocity_angular_distance;
			}else{
				aproach_velocity = ANGULAR_VELOCITY/reduce_velocity_angular_distance;
			}
			message->angular = aproach_velocity*distance_theta;
		}else{
			if(information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x != 0){
				message->angular = information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x*signum(distance_theta);
			}else{
				message->angular = ANGULAR_VELOCITY*signum(distance_theta);
			}
		}
	}
}

float Planning::calculateAngularVelocity(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg,
		theatrebot_action_modulation::ActionExecutionActionDescriptionMessage information_to_performed){
	float temp_angular_velocity = 0.0;
	if(!is_emotional_action_oscillate){
		if (information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
				!= 0) {
			temp_angular_velocity =
					information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x;
		} else {
			temp_angular_velocity = ANGULAR_VELOCITY;
		}
		if (forward_direction) {
			float distance_theta = msg->pose.orientation
					- tf::getYaw(
							information_to_performed.desire_position.desire_position.orientation);
			distance_theta = correctAngle(distance_theta);
			if ((distance_theta)
					>= information_to_performed.desire_position.desire_position.position.x) {
				forward_direction = !forward_direction;
			}
		} else {
			temp_angular_velocity = -1
					* temp_angular_velocity;
			float distance_theta = msg->pose.orientation
					- tf::getYaw(
							information_to_performed.desire_position.desire_position.orientation);
			distance_theta = correctAngle(distance_theta);
			if ((distance_theta)
					<= -information_to_performed.desire_position.desire_position.position.x) {
				forward_direction = !forward_direction;
			}
		}
	}else {
		if (information_to_performed.emotion_parameters[current_position_emotion].spacing
				!= 0) {
			//Here the action is emotional
			if (information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
					!= 0) {
				//TODO
			} else {
				temp_angular_velocity =
						information_to_performed.emotion_parameters[current_position_emotion].spacing
								/ information_to_performed.emotion_parameters[current_position_emotion].timing;
			}
			int f = information_to_performed.emotion_parameters.size();
			float distance_theta = msg->pose.orientation
					- tf::getYaw(
							information_to_performed.desire_position.desire_position.orientation);
			distance_theta = correctAngle(distance_theta);
			/*ROS_INFO("Action Emotional %f %f %f %f",
					distance_theta,
					information_to_performed.emotion_parameters[current_position_emotion].spacing,
					tf::getYaw(
						information_to_performed.desire_position.desire_position.orientation),
						msg->pose.orientation);*/
			if (forward_direction) {
				if (distance_theta
						>= information_to_performed.emotion_parameters[current_position_emotion].spacing) {
					forward_direction = !forward_direction;
					temp_angular_velocity = -1
					* temp_angular_velocity;
				}
			} else {
				temp_angular_velocity = -1
						* temp_angular_velocity;
				if (distance_theta
						<= -information_to_performed.emotion_parameters[current_position_emotion].spacing) {
					forward_direction = !forward_direction;
					temp_angular_velocity = -1
					* temp_angular_velocity;
				}
			}
			//ROS_INFO("ANGULAR VELOCITY %f",temp_angular_velocity);
		} else {
			float temp_angle = msg->pose.orientation;
			float aproach_velocity;
			float distance_theta =
					static_cast<float>(tf::getYaw(
							information_to_performed.desire_position.desire_position.orientation)
							- temp_angle);
			distance_theta = correctAngle(distance_theta);
			if (fabs(distance_theta) < reduce_velocity_angular_distance) {
				if (information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
						!= 0) {
					aproach_velocity =
							information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
									/ reduce_velocity_angular_distance;
				} else {
					aproach_velocity = ANGULAR_VELOCITY
							/ reduce_velocity_angular_distance;
				}
				temp_angular_velocity = aproach_velocity
						* distance_theta;
			} else {
				if (information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
						!= 0) {
					temp_angular_velocity =
							information_to_performed.trajectory_characteristic.trajectory_characteristic.angular.x
									* signum(distance_theta);
				} else {
					temp_angular_velocity = ANGULAR_VELOCITY
							* signum(distance_theta);
				}
			}
		}
	}
	return temp_angular_velocity;
}



void Planning::setIsEmotionalActionOScillate(bool is_emotional_action_oscillate){
	this->is_emotional_action_oscillate = is_emotional_action_oscillate;
}
void Planning::setInitialPosition(const theatrebot_action_modulation::OdometryTriskar::ConstPtr& msg){
	//Get the current pose, this is going to be used to all the calculations
	initial_pose.position.x = static_cast<float>(msg->pose.position.x);
	initial_pose.position.y = static_cast<float>(msg->pose.position.y);
	initial_pose.position.z = static_cast<float>(msg->pose.position.z);
	initial_pose.orientation =  static_cast<double>(msg->pose.orientation);
	//TODO implemented to a different parameters
}

void Planning::reset(){
	this->distance_travel = 0;
	this->temp_distance_traveled = 0;
	this->has_arrived = false;
	this->current_position_emotion = 0;
}

bool Planning::hasArrived(){
	return has_arrived;
}


float Planning::correctAngle(float distance_theta){
	if(distance_theta>M_PI){
		distance_theta= distance_theta-2.0*M_PI;
	}else if(distance_theta<-M_PI){
		distance_theta = distance_theta+2.0*M_PI;
	}
	return distance_theta;
}

float Planning::signum(float num){
	if(num<0)
		return -1;
	return 1;
}

float Planning::fabs(float num){
	if(num<0)
		return -1*num;
	return num;
}

void Planning::setControlAngle(bool control_angle){
	this->control_angle = control_angle;
}
