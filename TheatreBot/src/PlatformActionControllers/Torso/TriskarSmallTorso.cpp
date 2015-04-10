/*
 * TriskarSmallTorso.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: julian
 */

#include "TriskarSmallTorso.h"

TriskarSmallTorso::TriskarSmallTorso() {
	is_oscillating = false;
	//TODO define correctly the values for the triskar in radians. the new version all angles have a start in 0
	max_angle = static_cast<float>(M_PI_4);
	min_angle = static_cast<float>(-1*M_PI_4);
	current_angle = 0;
	angle_error = 0.04;
	velocity = 0.5; //TODO read this parameter from a file
	velocity_move = velocity;
	velocity_oscillate = velocity;
	delta_time = 0.1; //milli seconds
}

TriskarSmallTorso::~TriskarSmallTorso() {

}


void TriskarSmallTorso::setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//Here i am just interested in the vector orientation, the other parameter are not relevant in this case. However from emotion's definition is not possible to get the orientation
	//TODO see if is it interesting to add orientation to emotions' definition
	move_x = vector_x;
	move_y = vector_y;
	move_z = vector_z;
	//std::cout<<"Move torso: ";
	if(!is_moving){
		is_moving_emotional = true;
		generateEmotionalActionMove();
	}
}
void TriskarSmallTorso::setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_oscillation = repet;
	oscillate_x = vector_x;
	oscillate_y = vector_y;
	oscillate_z = vector_z;
	//std::cout<<"Oscillate torso: ";
	if(!is_oscillating){
		is_oscillating_emotional = true;
		generateEmotionalActionOscillate();
	}
	if(is_moving_emotional){
		is_moving_emotional = false;
	}
	generateEmotionalVelocityOscillate();
}

void TriskarSmallTorso::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_oscillate = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
		if(velocity_oscillate == 0){
			velocity_oscillate = velocity;
		}
	}else{
		velocity_oscillate = velocity;
	}
	//std::cout<<"Oscillate emotional "<<velocity_oscillate<<std::endl;
	//The other parameters are not consider here just because the robot at the moment does not have these two grades of freedom
}

void TriskarSmallTorso::synchEmotionMove(){
	if(pos_move_x<(move_x.size()-1)){
		pos_move_x++;
	}
	if(pos_move_x>=(move_x.size()-1)&&repeat_move){
		pos_move_x = 0;
	}
	//std::cout<<"Synch emotion move "<<pos_move_x<<std::endl;
	this->generateEmotionalActionMove();

}

void TriskarSmallTorso::synchEmotionOscillate(){
	if(pos_oscillate_x<(oscillate_x.size()-1)){
		pos_oscillate_x++;
	}
	if(pos_oscillate_x>=(oscillate_x.size()-1)&&repeat_oscillation){
		pos_oscillate_x = 0;
	}
	//std::cout<<"Synch emotion oscillate "<<pos_oscillate_x<<std::endl;
	this->generateEmotionalActionOscillate();
}

void TriskarSmallTorso::generateEmotionalActionMove(){
	Amplitude parameter;
	//std::cout<<"Generation move"<<move_x.at(0).getEmotionParameterSpacing()<<std::endl;
	if(move_x.size()>0){
		parameter.setDistanceX(move_x.at(pos_move_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	//std::cout<<parameter.getDistanceX()<<std::endl;
	this->MoveTorsoAction(parameter);
}

void TriskarSmallTorso::generateEmotionalActionOscillate(){
	//std::cout<<"Generating emotion "<<oscillate_x.size()<<" "<<pos_oscillate_x<<" v "<<oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing()<<std::endl;
	Amplitude parameter;
	if(oscillate_x.size()>0){
		//std::cout<<"It is going to do this!!"<<std::endl;
		parameter.setDistanceX(oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	//The other parameters are not consider here just because the robot at the moment does not have these two grades of freedom
	if(is_oscillating||is_oscillating_emotional){
		//std::cout<<parameter.getDistanceX()<<std::endl;
		this->OscillateTorsoAction(parameter);
	}
	generateEmotionalVelocityOscillate();
}

void TriskarSmallTorso::MoveTorsoAction(Amplitude parameter){
	//std::cout<<"Executing move"<<std::endl;
	is_moving_emotional = false;
	desire_angle_to_move = parameter.getDistanceX();
	verifyRange(&desire_angle_to_move,min_angle,max_angle);
	//std::cout<<"Angle "<<desire_angle_to_move<<std::endl;
	if(!is_oscillating&&!is_oscillating_emotional){
		is_moving = true;
		//Send command
		//float temp_position = this->sgn<float>(desire_angle_to_move);//*velocity_move*delta_time;
		//temp_position += current_angle;
		//verifyRange(&temp_position,min_angle,max_angle);
		this->sendMessage(desire_angle_to_move);
	}
}

void TriskarSmallTorso::OscillateTorsoAction(Amplitude parameter){
	//std::cout<<"Executing oscillate: "<<parameter.getDistanceX()<<" "<<parameter.getDistanceY()<<" "<<parameter.getDistanceZ()<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	verifyRange(&desire_angle_to_oscillate,min_angle,max_angle);
	//std::cout<<"Desire Angle "<<desire_angle_to_oscillate<<std::endl;
	if(!is_oscillating_emotional){
		is_oscillating = true;
		is_oscillating_emotional = false;
	}
}

void TriskarSmallTorso::setPublisherAction(ros::NodeHandle *node){
	pub_action_triskar = node->advertise<theatre_bot::TriskarSmallUpper>("servo_triskar", 1);
}

void TriskarSmallTorso::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("upper_triskar", 1, &TriskarSmallTorso::callbackUpdateTriskarUpper, this);
}

void TriskarSmallTorso::callbackUpdateTriskarUpper(const theatre_bot::Vector32::ConstPtr& msg){
	current_angle = static_cast<float>(msg->y/180.0*M_PI);
	//std::cout<<"Current "<<current_angle<<" desire "<<desire_angle_to_move<<std::endl;
	if(is_moving||is_moving_emotional){
		if(current_angle>=(desire_angle_to_move-angle_error)&&current_angle<=(desire_angle_to_move+angle_error)){
			//std::cout<<"It has finish"<<std::endl;
			is_moving = false;
			is_moving_emotional = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_name_move;
			message.coming_to = "";
			message.message = "action_finished";
			this->stopMoveTorsoAction();
			pub_action_synch->publish(message);
		}
	}
	if(is_oscillating||is_oscillating_emotional){
		//std::cout<<"Oscillating torso "<<is_oscillating<<" or "<<is_oscillating_emotional<<" velocity "<<velocity_oscillate<<" current angle "<<current_angle<<" min "<<min_angle<<" desire angel to move "<<desire_angle_to_move<<" desire angle to oscillate "<<desire_angle_to_oscillate<<std::endl;
		float desire_velocity = this->updateOscillation(velocity_oscillate,current_angle,min_angle,max_angle,desire_angle_to_move,desire_angle_to_oscillate,angle_error,&forward_direction_x);
		float next_position = current_angle + desire_velocity *delta_time;
		std::cout<<current_angle<<" vel: "<<velocity_oscillate<<" oscillation "<<desire_angle_to_oscillate<<" angle "<<desire_angle_to_move<<std::endl;
		verifyRange(&next_position,min_angle,max_angle);
		sendMessage(next_position);
	}
}

void TriskarSmallTorso::sendMessage(float position){
	theatre_bot::TriskarSmallUpper message;
	this->initMessageTriskar(&message);
	//std::cout<<" dfaf "<< position<<std::endl;
	message.center = static_cast<float>(position/static_cast<float>(M_PI)*180.0);
	message.center_change = true;
	pub_action_triskar.publish(message);

}
void TriskarSmallTorso::stopMoveTorsoAction(){
	is_moving = false;
	is_moving_emotional = false;
	repeat_move = false;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	this->velocity_move = this->velocity;
}

void TriskarSmallTorso::stopOscillateTorsoAction(){
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	velocity_oscillate = velocity;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	pos_oscillate_z = 0;
	this->velocity_oscillate_x = this->velocity;
	this->velocity_oscillate_y = this->velocity;
	this->velocity_oscillate_z = this->velocity;
	desire_angle_to_oscillate = 0;
	desire_angle_to_oscillate_y = 0;
	desire_angle_to_oscillate_z = 0;
	ROS_INFO("Oscillate torso finish");
}

void TriskarSmallTorso::initMessageTriskar(theatre_bot::TriskarSmallUpper *message){
	message->center_change = false;
	message->left_change = false;
	message->right_change = false;
}
