/*
 * TriskarSmallBody.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#include "TriskarSmallBody.h"

TriskarSmallBody::TriskarSmallBody() {
	yaw_error = static_cast<float>(1.5/180.0*M_PI);
	velocity_rotate = 1.8; //rad/sec;
	reduce_linear_velocity = 250.0; //mm
	reduce_angular_velocity = static_cast<float>(5.0/180.0*M_PI); //rad
	linear_velocity = 500.0; //mm/sec
	x_error = 20.0; //mm
	y_error = 20.0; //mm
	has_arrived = false;
	robot_initial_position_x = 0.0;
	robot_initial_position_y = 0.0;
	robot_initial_position_z = 0.0;
	robot_initial_angle = 0.0;
	emotional_distance = 0.0;
	initial_emotional_distance = 0.0;
	maximum_error_theta = 0.0;
	triskar_planner.setVariables(yaw_error,velocity_rotate,linear_velocity,reduce_linear_velocity,reduce_angular_velocity,x_error,y_error);
}

TriskarSmallBody::~TriskarSmallBody() {
	// TODO Auto-generated destructor stub
}


void TriskarSmallBody::setPublisherAction(ros::NodeHandle *node){
	pub_action_triskar = node->advertise<theatre_bot::TriskarVelocity>("vel_triskar",10);
	pub_command_triskar = node->advertise<std_msgs::Char>("commands_triskar",10);
}


void TriskarSmallBody::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("odometry_triskar",1, &TriskarSmallBody::callBackUpdateTriskar, this);
}

void TriskarSmallBody::MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position){
	is_moving = true;
	has_arrived = false;
	triskar_planner.setTypeParameter(type_position);
	if(type_position == PointPosition){
		boost::shared_ptr<Point> parameter_point = boost::static_pointer_cast<Point>(parameter);
		//Change to the position to the robot's reference
		parameter_point->setX(parameter_point->getX()-robot_initial_position_x);
		parameter_point->setY(parameter_point->getY()-robot_initial_position_y);
		//Set point in the planner
		triskar_planner.setPoint(parameter_point);
	}else if(type_position == LandmarkPosition){
		boost::shared_ptr<Landmark> parameter_landmark = boost::static_pointer_cast<Landmark>(parameter);
		//Set information in the planner
		triskar_planner.setLandmark(parameter_landmark);
	}else if(type_position == SquarePosition){
		boost::shared_ptr<Square> parameter_square = boost::static_pointer_cast<Square>(parameter);
		//Set information in the planner
		triskar_planner.setSquare(parameter_square);
	}else if(type_position == CirclePosition){
		boost::shared_ptr<Circle> parameter_circle = boost::static_pointer_cast<Circle>(parameter);
		//Set information in the planner
		triskar_planner.setCircle(parameter_circle);
	}
}

void TriskarSmallBody::OscillateBodyAction(Amplitude parameter){
	//std::cout<<"Updating Oscillate body"<<std::endl;
	desire_angle_to_oscillate_yaw = parameter.getDistanceZ();
	desire_angle_to_oscillate_roll = parameter.getDistanceX();
	desire_angle_to_oscillate_pitch = parameter.getDistanceY();
	//std::cout<<"yaw "<<desire_angle_to_oscillate_yaw<<std::endl;
	verifyAngle(&desire_angle_to_oscillate_pitch);
	verifyAngle(&desire_angle_to_oscillate_roll);
	verifyAngle(&desire_angle_to_oscillate_yaw);
	if(!is_oscillating_emotional){
		is_oscillating_emotional = false;
		is_oscillating = true;
	}
}

void TriskarSmallBody::stopMoveBodyAction(){
	is_moving = false;
	repeat_move = false;
	is_moving_emotional = false;
	has_arrived = false;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	velocity_emotional_rotate = velocity_rotate;
	triskar_planner.setVariables(yaw_error,velocity_rotate,linear_velocity,reduce_linear_velocity,reduce_angular_velocity,x_error,y_error);
	std_msgs::Char t;
	t.data = 'S';
	pub_command_triskar.publish(t);
	ROS_INFO("action move body has finished");
}

void TriskarSmallBody::stopOscillateBodyAction(){
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	velocity_emotional_rotate = velocity_rotate;
	velocity_oscillate_yaw = velocity_rotate;
	pos_oscillate_x = 0.0;
	triskar_planner.setVariables(yaw_error,velocity_rotate,linear_velocity,reduce_linear_velocity,reduce_angular_velocity,x_error,y_error);
	std_msgs::Char t;
	t.data = 'S';
	pub_command_triskar.publish(t);
	ROS_INFO("action oscillate body has finished");
}

void TriskarSmallBody::synchEmotionMove(){
	//std::cout<<"Synch move actions"<<std::endl;
	if(pos_move_x<(move_x.size()-1)){
		//std::cout<<"Moving in the array move"<<std::endl;
		pos_move_x++;
	}
	//std::cout<<"Pos "<<pos_move_x<<" "<<(move_x.size()-1)<<" "<<repeat_move<<std::endl;
	if(pos_move_x>=(move_x.size()-1)&&repeat_move){
		pos_move_x = 0;
		initial_emotional_distance = triskar_planner.getCurrentDistance();
	}else if(pos_move_x>=(move_x.size()-1)&&!repeat_move){
		//std::cout<<"Is not going to repeat"<<std::endl;
		is_moving_emotional = false;
	}
	//std::cout<<"Synch move "<<pos_move_x<<std::endl; address
	this->generateEmotionalActionMove();
}

void TriskarSmallBody::generateEmotionalActionMove(){
	if(move_x.size()>0){
		emotional_distance = move_x.at(pos_move_x).getEmotionParameterSpacing();
	}else{
		emotional_distance = 0;
	}
	//std::cout<<"Move pos "<<emotional_distance<<std::endl;
	this->generateEmotionalVelocityMove();
}

void TriskarSmallBody::generateEmotionalVelocityMove(){
	if(move_x.size()>0){
		float desire_velocity = move_x.at(pos_move_x).getEmotionParameterTime();
		//std::cout<<"Velocity move "<<desire_velocity<<std::endl;
		triskar_planner.setVelocities(desire_velocity,(desire_velocity/linear_velocity)*velocity_rotate);
	}else{
		//std::cout<<"Velocity move "<<linear_velocity<<std::endl;
		triskar_planner.setVelocities(linear_velocity,velocity_rotate);
	}
}

void TriskarSmallBody::synchEmotionOscillate(){
	std::cout<<"Synch oscillate actions"<<std::endl;
	if(pos_oscillate_x<(oscillate_x.size()-1)){
		//std::cout<<"Updating x oscillate body"<<std::endl;
		pos_oscillate_x++;
	}
	if(pos_oscillate_y<(oscillate_y.size()-1)){
		pos_oscillate_y++;
	}
	if(pos_oscillate_z<(oscillate_z.size()-1)){
		pos_oscillate_z++;
	}
	if(pos_oscillate_x>=(oscillate_x.size()-1)&&pos_oscillate_y>=(oscillate_y.size()-1)&&pos_oscillate_z>=(oscillate_z.size()-1)&&repeat_oscillation){
		//std::cout<<"Oscillate start from 0"<<std::endl;
		pos_oscillate_x = 0;
		pos_oscillate_y = 0;
		pos_oscillate_z = 0;
	}
	std::cout<<"Synch oscillate "<<pos_oscillate_x<<std::endl;
	this->generateEmotionalActionOscillate();
}
void TriskarSmallBody::setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//std::cout<<"repeat "<<repet<<std::endl;
	repeat_move = repet;
	initial_emotional_distance = triskar_planner.getCurrentDistance();
	move_x = vector_x;
	is_moving_emotional = true;
	//std::cout<<"Move emotional "<<initial_emotional_distance<<std::endl;
	generateEmotionalActionMove();
	generateEmotionalVelocityMove();
}

void TriskarSmallBody::setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_oscillation = repet;
	oscillate_x = vector_x;
	oscillate_y = vector_y;
	oscillate_z = vector_z;
	if(!is_oscillating){
		//std::cout<<"It is moving emotionally"<<std::endl;
		is_oscillating_emotional = true;
		generateEmotionalActionOscillate();
	}
	generateEmotionalVelocityOscillate();
}

void TriskarSmallBody::generateEmotionalActionOscillate(){
	Amplitude parameter;
	if(oscillate_x.size()>0){
		//std::cout<<"size different of zero and distance "<<oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing()<<" in pos "<<pos_oscillate_x<<std::endl;
		parameter.setDistanceZ(oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing());
	}else{
		//std::cout<<"the size is 0"<<std::endl;
		parameter.setDistanceZ(0);
	}
	if(oscillate_y.size()>0){
		parameter.setDistanceY(oscillate_y.at(pos_oscillate_y).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceY(0);
	}
	if(oscillate_z.size()>0){
		parameter.setDistanceX(oscillate_z.at(pos_oscillate_z).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	if(is_oscillating||is_oscillating_emotional){
		this->OscillateBodyAction(parameter);
	}
}

void TriskarSmallBody::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		//std::cout<<"The vector has elements and the velocity is "<<oscillate_x.at(pos_oscillate_x).getEmotionParameterTime()<<" in pos "<<pos_oscillate_x<<std::endl;
		velocity_oscillate_yaw = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
	}else{
		//std::cout<<"The vector does not have velocity elements"<<std::endl;
		velocity_oscillate_yaw = velocity_rotate;
	}
}

void TriskarSmallBody::callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg){
	bool send_message = false;
	theatre_bot::TriskarVelocity message;
	x =robot_initial_position_x + cos(robot_initial_angle)*msg->pose.position.x-sin(robot_initial_angle)*msg->pose.position.y;
	y =robot_initial_position_y +sin(robot_initial_angle)*msg->pose.position.x + cos(robot_initial_angle)*msg->pose.position.y;
	yaw = robot_initial_angle + msg->pose.orientation;
	this->verifyAngle(&yaw);
	//std::cout<<"X: "<<x<<" Y: "<<y<<" theta: "<<yaw<<std::endl;
	if(is_moving||is_moving_emotional){
		if(is_moving_emotional){//Add the emotional movements
			//std::cout<<"Is moving emotional current emotional distance "<<emotional_distance<<" triskar current distance "<<triskar_planner.getCurrentDistance()<<" initial emotional distance "<<initial_emotional_distance<<std::endl;
			if(emotional_distance<(triskar_planner.getCurrentDistance()-initial_emotional_distance)){
				initial_emotional_distance = triskar_planner.getCurrentDistance();
				//synch emotional
				theatre_bot::ActionExecutionMessage message;
				message.coming_from = this->action_move_name;
				message.coming_to = "";
				message.message = "emotion_synch";
				//std::cout<<"It has send emotional synch"<<std::endl;
				pub_action_synch->publish(message);

			}
		}
		if(!has_arrived){
			send_message = true;
			//Calculate linear velocity
			has_arrived = triskar_planner.updateLinearVelocity(x,y,yaw,&message,this->theatre_place);
			//std::cout<<"it has angle: "<<triskar_planner.getHasAngle()<<" it is reducing velocity "<<triskar_planner.isReducingVelocity()<<std::endl;
			if(triskar_planner.getHasAngle()&&triskar_planner.isReducingVelocity()){
				//std::cout<<"it getting close to the end"<<std::endl;
				is_oscillating = false;
				is_oscillating_emotional = false;
			}
			if(!(is_oscillating||is_oscillating_emotional)){
				//Calculate angular velocity
				bool temp_arrive = triskar_planner.updateAngularVelocity(yaw,&message);
				has_arrived = has_arrived && temp_arrive;
				//std::cout<<" it has arrive (angle) "<<has_arrived<<std::endl;
			}
		}else{
			is_moving = false;
			is_moving_emotional = false;
			//Send synch message
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_move_name;
			message.coming_to = "";
			message.message = "action_finished";
			pub_action_synch->publish(message);
			std_msgs::Char t;
			t.data = 'S';
			this->stopMoveBodyAction();
			pub_command_triskar.publish(t);
		}
	}
	//std::cout<<"is oscillating "<<is_oscillating<<" emotional oscillating "<<is_oscillating_emotional<<std::endl;
	if(is_oscillating||is_oscillating_emotional){
		send_message = true;
		//Calculate angular velocity
		float desire_velocity_yaw = this->updateOscillation(velocity_oscillate_yaw,yaw,triskar_planner.getDesireYaw(),desire_angle_to_oscillate_yaw,yaw_error,&forward_direction_yaw);
		//std::cout<<"Setting angular velocity "<<desire_velocity_yaw<<" desire angle "<<desire_angle_to_oscillate_yaw<<" current angle "<<yaw<<std::endl;
		message.angular = desire_velocity_yaw;
	}
	if(send_message){
		//Send message to triskar
		std::cout<<"sending message x: "<<message.linear.x<<" y: "<<message.linear.y<<" theta: "<<message.angular<<std::endl;
		pub_action_triskar.publish(message);
	}
}
