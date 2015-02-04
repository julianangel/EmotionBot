/*
 * KeeponBody.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#include "KeeponBody.h"

KeeponBody::KeeponBody() {
	yaw_error = static_cast<float>(5.0/180.0*M_PI);
	delta_time = 0.1;//mms
}

KeeponBody::~KeeponBody() {
	// TODO Auto-generated destructor stub
}

void KeeponBody::setPublisherAction(ros::NodeHandle *node){
	pub_action_keepon = node->advertise<theatre_bot::KeeponMessage>("keepon_action", 10);
}

void KeeponBody::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("keepon_information", 1, &KeeponBody::callbackUpdateKeepon, this);
}

/*
 * keepon's capabilities do not have the possibility to move the body,
 * it is going to get the position regardless the rest of the information
 */
void KeeponBody::MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position){
	is_moving = true;
	if(parameter->getHasPose()){
		tf::Quaternion q(parameter->getQuaterionX(),parameter->getQuaterionY(),parameter->getQuaterionZ(),parameter->getQuaterionW());
		tf::Matrix3x3 m(q);
		double roll, pitch, yaw;
		m.getRPY(roll, pitch, yaw);
		desire_yaw = static_cast<float>(yaw);
		std::cout<<"It is working is going to change the body orientation"<<std::endl;
		if(!is_oscillating||!is_oscillating_emotional){
			theatre_bot::KeeponMessage message;
			this->initMessageKeepon(&message);
			verifyAngle(&desire_yaw);
			message.pan.data = static_cast<float>(desire_yaw/M_PI*180.0);
			message.pan_change = true;
			pub_action_keepon.publish(message);
		}
	}
}

void KeeponBody::OscillateBodyAction(Amplitude parameter){
	std::cout<<"Oscillate body"<<std::endl;
	is_oscillating_emotional = false;
	desire_angle_to_oscillate_yaw = parameter.getDistanceZ();
	desire_angle_to_oscillate_roll = parameter.getDistanceX();
	desire_angle_to_oscillate_pitch = parameter.getDistanceY();
	verifyAngle(&desire_angle_to_oscillate_pitch);
	verifyAngle(&desire_angle_to_oscillate_roll);
	verifyAngle(&desire_angle_to_oscillate_yaw);
	is_oscillating = true;
}

void KeeponBody::stopMoveBodyAction(){
	std::cout<<"Stopping move"<<std::endl;
	is_moving = false;
	is_moving_emotional = 0;
	velocity_emotional_rotate = velocity_rotate;
}

void KeeponBody::stopOscillateBodyAction(){
	std::cout<<"Stopping oscillate"<<std::endl;
	is_oscillating = false;
	is_oscillating_emotional = false;
	velocity_emotional_rotate = velocity_rotate;
}

void KeeponBody::synchEmotionMove(){

}

void KeeponBody::synchEmotionOscillate(){

}

void KeeponBody::callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg){
	yaw =  static_cast<float>(msg->pan.data/180.0*M_PI);
	if(is_moving){
		if(yaw>=(desire_yaw-yaw_error)&&yaw<=(desire_yaw+yaw_error)){
			std::cout<<"Finishing Move"<<std::endl;
			is_moving = false;
			is_moving_emotional = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_move_name;
			message.coming_to = "";
			message.message = "action_finished";
			pub_action_synch->publish(message);
		}
	}
	if(is_oscillating || is_oscillating_emotional){
		std::cout<<"It is oscillating"<<std::endl;
		float desire_velocity_yaw = this->updateOscillation(velocity_emotional_rotate,yaw,desire_yaw,desire_angle_to_oscillate_yaw,yaw_error,&forward_direction_yaw);
		float next_position_yaw = yaw + desire_velocity_yaw*delta_time;
		verifyAngle(&next_position_yaw);
		std::cout<<"Desire angle "<<desire_yaw<<" desire velocity "<<desire_velocity_yaw<<" next position "<<next_position_yaw<<std::endl;
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		message.pan.data =  static_cast<float>(next_position_yaw/static_cast<float>(M_PI)*180.0);
		if(desire_angle_to_oscillate_yaw != 0){
			message.pan_change = true;
		}
		pub_action_keepon.publish(message);
	}
}

void KeeponBody::initMessageKeepon(theatre_bot::KeeponMessage *message){
	message->tilt_change = false;
	message->pan_change = false;
	message->side_change = false;
	message->pon_change = false;
}
