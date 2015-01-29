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
}

KeeponTorso::~KeeponTorso() {
	// TODO Auto-generated destructor stub
}


void KeeponTorso::MoveTorsoAction(Amplitude parameter){
	std::cout<<"Done"<<std::endl;
	desire_angle_to_move = parameter.getDistanceX();
	desire_angle_to_side = parameter.getDistanceY();
	if(!is_oscillating){
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		if(desire_angle_to_move<min_tilt){
			desire_angle_to_move = min_tilt;
		} else if(desire_angle_to_move>max_tilt){
			desire_angle_to_move = max_tilt;
		}
		if(desire_angle_to_side<min_side){
			desire_angle_to_side = min_side;
		} else if(desire_angle_to_side>max_side){
			desire_angle_to_side = max_side;
		}
		message.side.data = static_cast<float>(desire_angle_to_side/static_cast<float>(M_PI)*180.0);
		message.side_change = true;
		message.tilt.data = static_cast<float>(desire_angle_to_move/static_cast<float>(M_PI)*180.0);
		message.tilt_change = true;

		pub_action_keepon.publish(message);
	}
}

void KeeponTorso::OscillateTorsoAction(Amplitude parameter){
	std::cout<<"Done 2"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	if(desire_angle_to_oscillate<min_tilt){
		desire_angle_to_oscillate = min_tilt;
	} else if(desire_angle_to_oscillate>max_tilt){
		desire_angle_to_oscillate = max_tilt;
	}
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
	if(is_oscillating){
		float desire_velocity = this->updateOscillation(velocity,tilt,min_tilt,max_tilt);
		float next_position = tilt + desire_velocity *delta_time;
		//Send message
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		if(next_position<min_tilt){
			next_position = min_tilt;
		} else if(next_position>max_tilt){
			next_position = max_tilt;
		}
		message.tilt.data = static_cast<float>(next_position/static_cast<float>(M_PI)*180.0);
		message.tilt_change = true;
		pub_action_keepon.publish(message);
	}
}

void KeeponTorso::stopMoveTorsoAction(){
	//TODO
	ROS_INFO("Move torso finish");
}

void KeeponTorso::stopOscillateTorsoAction(){
	is_oscillating = false;
	ROS_INFO("Oscillate torso finish");
}
