/*
 * TriskarSmallTorso.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: julian
 */

#include "TriskarSmallTorso.h"

TriskarSmallTorso::TriskarSmallTorso() {
	is_oscillating = false;
	//TODO define correctly the values for the triskar
	max_angle = 0;
	min_angle = 0;
	current_angle = 0;
	velocity = 1; //TODO read this parameter from a file
	delta_time = 100; //milli seconds
}

TriskarSmallTorso::~TriskarSmallTorso() {

}


void TriskarSmallTorso::setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//TODO
}
void TriskarSmallTorso::setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//TODO
}

void TriskarSmallTorso::synchEmotionMove(){
	//TODO
}

void TriskarSmallTorso::synchEmotionOscillate(){
	//TODO
}

void TriskarSmallTorso::generateEmotionalActionMove(){
	//TODO
}

void TriskarSmallTorso::generateEmotionalActionOscillate(){
	//TODO
}

void TriskarSmallTorso::MoveTorsoAction(Amplitude parameter){
	std::cout<<"Executing move"<<std::endl;
	desire_angle_to_move = parameter.getDistanceX();
	if(!is_oscillating){
		//Send command
		this->sendMessage(desire_angle_to_move);
	}
}

void TriskarSmallTorso::OscillateTorsoAction(Amplitude parameter){
	std::cout<<"Executing oscillate"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	if(desire_angle_to_oscillate<min_angle){
		desire_angle_to_oscillate = min_angle;
	} else if(desire_angle_to_oscillate > max_angle){
		desire_angle_to_oscillate = max_angle;
	}
	is_oscillating = true;
}

void TriskarSmallTorso::setPublisherAction(ros::NodeHandle *node){
	pub_action_triskar = node->advertise<theatre_bot::TriskarSmallUpper>("servo_triskar", 1);
}

void TriskarSmallTorso::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("triskar_upper_information", 1, &TriskarSmallTorso::callbackUpdateTriskarUpper, this);
}

void TriskarSmallTorso::callbackUpdateTriskarUpper(const theatre_bot::TriskarSmallUpper::ConstPtr& msg){
	current_angle = static_cast<float>(msg->center);
	if(is_oscillating){
		float desire_velocity = this->updateOscillation(velocity,current_angle,min_angle,max_angle);
		float next_position = current_angle + desire_velocity *delta_time;
		//Send command
		this->sendMessage(next_position);
	}
}

void TriskarSmallTorso::sendMessage(float position){
	theatre_bot::TriskarSmallUpper message;
	this->initMessageTriskar(&message);
	message.center = position;
	message.center_change = true;
	pub_action_triskar.publish(message);

}
void TriskarSmallTorso::stopMoveTorsoAction(){
	ROS_INFO("Move torso finish");
}

void TriskarSmallTorso::stopOscillateTorsoAction(){
	is_oscillating = false;
	ROS_INFO("Oscillate torso finish");
}

void TriskarSmallTorso::initMessageTriskar(theatre_bot::TriskarSmallUpper *message){
	message->center_change = false;
	message->left_change = false;
	message->right_change = false;
}
