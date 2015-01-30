/*
 * KeeponTorso.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#include "KeeponTorso.h"

KeeponTorso::KeeponTorso() {
	this->tilt = 0;
	this->min_tilt = static_cast<float>(-1*M_PI)/4.0;
	this->max_tilt = static_cast<float>(M_PI)/4.0;
	this->side = 0;
	this->min_side = static_cast<float>(-1*M_PI)*5.0/36.0;
	this->max_side = static_cast<float>(M_PI)*5.0/36.0;
	this->is_oscillating = false;
	this->desire_angle_to_oscillate = 0;
	this->delta_time = 0.1; //s
	this->velocity = 1; //ras/sec
	this->pon = 0;
	this->min_pon = 0;
	this->max_pon = 15;
	this->tilt_error = 0.08;
	this->side_error = 0.5;
	this->pon_error = 2;
}

KeeponTorso::~KeeponTorso() {
	// TODO Auto-generated destructor stub
}


void KeeponTorso::MoveTorsoAction(Amplitude parameter){
	std::cout<<"Done"<<std::endl;
	desire_angle_to_move = parameter.getDistanceX();
	desire_angle_to_side = parameter.getDistanceY();
	desire_angle_to_z = parameter.getDistanceZ();
	if(!is_oscillating){
		is_moving = true;
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		verifyRange(&desire_angle_to_move,min_tilt,max_tilt);
		verifyRange(&desire_angle_to_side,min_side,max_side);
		verifyRange(&desire_angle_to_z,min_pon,max_pon);
		message.side.data = static_cast<float>(desire_angle_to_side/static_cast<float>(M_PI)*180.0);
		message.side_change = true;
		message.tilt.data = static_cast<float>(desire_angle_to_move/static_cast<float>(M_PI)*180.0);
		message.tilt_change = true;
		message.pon.data = desire_angle_to_z;
		message.pon_change = true;
		pub_action_keepon.publish(message);
	}
}

void KeeponTorso::OscillateTorsoAction(Amplitude parameter){
	std::cout<<"Done 2"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	desire_angle_to_oscillate_y = parameter.getDistanceY();
	desire_angle_to_oscillate_z = parameter.getDistanceZ();
	verifyRange(&desire_angle_to_oscillate,min_tilt,max_tilt);
	verifyRange(&desire_angle_to_oscillate_y,min_side,max_side);
	verifyRange(&desire_angle_to_oscillate_z,min_pon,max_pon);
	is_oscillating = true;
}

void KeeponTorso::setPublisherAction(ros::NodeHandle *node){
	pub_action_keepon = node->advertise<theatre_bot::KeeponMessage>("keepon_action", 10);
}


void KeeponTorso::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("keepon_information", 1, &KeeponTorso::callbackUpdateKeepon, this);
}

void KeeponTorso::initMessageKeepon(theatre_bot::KeeponMessage *message){
	message->tilt_change = false;
	message->pan_change = false;
	message->side_change = false;
	message->pon_change = false;
}


void KeeponTorso::callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg){
	this->tilt = static_cast<float>(msg->tilt.data/180.0*M_PI);
	this->side = static_cast<float>(msg->side.data/180.0*M_PI);
	this->pon = msg->pon.data;
	if(is_moving){
		if(tilt>=(desire_angle_to_move-tilt_error)&&tilt<=(desire_angle_to_move+tilt_error)){
			std::cout<<"Finishing"<<std::endl;
			is_moving = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_name_move;
			message.coming_to = "";
			message.message = "action_finished";
			pub_action_synch->publish(message);

		}
	}
	if(is_oscillating){
		float desire_velocity_x = this->updateOscillation(velocity,tilt,min_tilt,max_tilt,desire_angle_to_move,desire_angle_to_oscillate,tilt_error,&forward_direction_x);
		float desire_velocity_y = this->updateOscillation(velocity,side,min_side,max_side,desire_angle_to_side,desire_angle_to_oscillate_y,side_error,&forward_direction_y);
		float desire_velocity_z = this->updateOscillation(velocity,pon,min_pon,max_pon,desire_angle_to_z,desire_angle_to_oscillate_z,pon_error,&forward_direction_z);
		//std::cout<<"X "<<desire_velocity_x<<" Y "<<desire_velocity_y<<" Z "<<desire_velocity_z<<std::endl;
		float next_position_x = tilt + desire_velocity_x *delta_time;
		float next_position_y = side + desire_velocity_y *delta_time;
		float next_position_z = pon + desire_velocity_z *delta_time;
		//Send message
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		verifyRange(&next_position_x,min_tilt,max_tilt);
		verifyRange(&next_position_y,min_side,max_side);
		verifyRange(&next_position_z,min_pon,max_pon);
		message.tilt.data = static_cast<float>(next_position_x/static_cast<float>(M_PI)*180.0);
		message.side.data = static_cast<float>(next_position_y/static_cast<float>(M_PI)*180.0);
		message.pon.data = next_position_z;
		if(desire_angle_to_oscillate!=0)
			message.tilt_change = true;
		if(desire_angle_to_oscillate_y!=0)
			message.side_change = true;
		if(desire_angle_to_oscillate_z!=0)
			message.pon_change = true;
		pub_action_keepon.publish(message);
	}
}

void KeeponTorso::stopMoveTorsoAction(){
	is_moving = false;
	theatre_bot::KeeponMessage message;
	this->initMessageKeepon(&message);
	message.side.data = 0.0;
	message.side_change = true;
	message.tilt.data = 0.0;
	message.tilt_change = true;
	message.pon.data = 0.0;
	message.pon_change = true;
	pub_action_keepon.publish(message);
	ROS_INFO("Move torso finish");
}

void KeeponTorso::stopOscillateTorsoAction(){
	is_oscillating = false;
	desire_angle_to_oscillate = 0;
	desire_angle_to_oscillate_y = 0;
	desire_angle_to_oscillate_z = 0;
	ROS_INFO("Oscillate torso finish");
}
