#include "BodyController.h"


BodyController::BodyController(){
	//Linear movement
	reduce_linear_velocity = 60.0; //mm
	linear_velocity = 500.0; //mm/sec
	current_linear_velocity = linear_velocity;
	x_error = 15.0; //mm
	y_error = 15.0; //mm
	maximum_linear_velocity = 1250.0;
	is_moving = false;
	has_arrived = false;
	desire_x = 0.0;
	desire_y = 0,0;
	desire_theta = 0.0;
	current_distance = 0.0;
	is_reducing_velocity = false;
	has_arrived_linear = false;
	has_arrived_angular = false;
	//Angular movement
	angular_velocity = 2; //rad/sec;
	yaw_error = static_cast<float>(1.5/180.0*M_PI);
	reduce_angular_velocity = static_cast<float>(5.0/180.0*M_PI); //rad
	maximum_error_theta = 0.0;
	maximum_angular_velocity = 3.5;
	desire_angle_to_oscillate_yaw = 0.0;
	is_oscillating = false;	
	velocity_oscillate_yaw = angular_velocity;
	forward_direction_yaw = false;
	//Linear emotional movement
	//emotional_distance = 0.0;
	//initial_emotional_distance = 0.0;
	//repeat_move = false;
	//is_moving_emotional = false;
	//pos_move = 0;
	//move_emotion_synch = false;
	//max_size = 15;
	//size_move_emotion = 0;
	//Angular emotional movement
	//size_oscillate_emotion = 0;
	//is_oscillating_emotional = false;
	//repeat_oscillation = false;
	//pos_oscillate_yaw = 0;
	//Temporal values
	this->last_position_x = 0.0;
	this->last_position_y = 0.0;
	//
	desire_velocity_x = 0.0;
	desire_velocity_y = 0.0;
	desire_velocity_theta = 0.0;
}

BodyController::~BodyController(){
}

float BodyController::getDesireVelocityX(){
	return desire_velocity_x;
}

float BodyController::getDesireVelocityY(){
	return desire_velocity_y;
}

float BodyController::getDesireVelocityTheta(){
	return desire_velocity_theta;
}

void BodyController::setVelocity(float linear, float angular){
	this->reduce_linear_velocity = linear/8.333;
	this->reduce_angular_velocity = angular/18.0;
	this->linear_velocity = linear;
	this->angular_velocity = angular;
	this->current_linear_velocity = this->linear_velocity;
	this->velocity_oscillate_yaw = this->angular_velocity;
}

void BodyController::OscillateBodyAction(float yaw){
	desire_angle_to_oscillate_yaw = yaw;
	if(desire_angle_to_oscillate_yaw != 0.0){
		is_oscillating = true;
		verifyAngle(&desire_angle_to_oscillate_yaw);
	}
}

void BodyController::MoveBodyAction(float position_x,float position_y, float position_theta){
	is_moving = true;
	has_arrived = false;
	has_arrived_linear = false;
	has_arrived_angular = false;
	this->desire_x = position_x;
	this->desire_y = position_y;
	this->desire_theta = position_theta;
	this->is_reducing_velocity = false;
}

void BodyController::verifyAngle(float *angle){
	if(*angle>M_PI){
		*angle= *angle-2.0*M_PI;
	}else if(*angle<-M_PI){
		*angle = *angle+2.0*M_PI;
	}
}

void BodyController::stopMoveBodyAction(){
	is_moving = false;
	//repeat_move = false;
	//is_moving_emotional = false;
	has_arrived = false;
	has_arrived_linear = false;
	has_arrived_angular = false;
	//move_emotion_synch = false;
	//pos_move = 0;
	//size_move_emotion = 0;
	this->current_linear_velocity = this->linear_velocity;
	//velocity_oscillate_yaw = angular_velocity;
}

/*bool BodyController::getEmotionalSynch(){
	return move_emotion_synch;
}*/

/*void BodyController::setEmotionalSynch(bool set_value){
	this->move_emotion_synch = set_value;
}*/

void BodyController::stopOscillateBodyAction(){
	is_oscillating = false;
	//is_oscillating_emotional = false;
	//repeat_oscillation = false;
	velocity_oscillate_yaw = angular_velocity;
	desire_angle_to_oscillate_yaw = 0.0;
	//size_oscillate_emotion = 0;
	//pos_oscillate_yaw = 0.0;
}

/*void BodyController::synchEmotionMove(){
	//TODO get the vector move_x
	if(pos_move<(size_move_emotion-1)){
		pos_move++;
	}
	if(pos_move>=(size_move_emotion-1)&&repeat_move){
		pos_move = 0;
		initial_emotional_distance = current_distance;
	}else if(pos_move>=(size_move_emotion-1)&&!repeat_move){
		is_moving_emotional = false;
	}
	this->generateEmotionalActionMove();
}*/

/*void BodyController::generateEmotionalActionMove(){
	if(size_move_emotion>0){
		emotional_distance = move_emotional_distance[pos_move];
	}else{
		emotional_distance = 0;
	}
	generateEmotionalVelocityMove();
}*/

/*void BodyController::generateEmotionalVelocityMove(){
	if(size_move_emotion>0){
		current_linear_velocity = move_emotional_velocity[pos_move];
		if(current_linear_velocity>maximum_linear_velocity)
			current_linear_velocity = maximum_linear_velocity;
	}else{
		current_linear_velocity = linear_velocity;
	}
}*/

/*void BodyController::synchEmotionOscillate(){
	//TODO get the vector oscillate z
	if(pos_oscillate_yaw<(size_oscillate_emotion-1)){
		pos_oscillate_yaw++;
	}
	if(pos_oscillate_yaw>=(size_oscillate_emotion-1)&&repeat_oscillation){
		pos_oscillate_yaw = 0;
	}
	this->generateEmotionalActionOscillate();
}*/

/*void BodyController::generateEmotionalActionOscillate(){
	float parameter_yaw;
	if(size_oscillate_emotion>0){
		parameter_yaw = (oscillate_emotional_distance[pos_oscillate_yaw]);
	}else{
		parameter_yaw = 0.0;
	}
	if(is_oscillating||is_oscillating_emotional){
		this->OscillateBodyAction(parameter_yaw);
	}
	generateEmotionalVelocityOscillate();
}*/

/*void BodyController::setEmotionalMoveBody(bool repeat, int quantity, float distance[15],float velocity[15]){
	repeat_move = repeat;
	this->initial_emotional_distance = this->current_distance;
	this->is_moving_emotional = true;
	this->pos_move = 0;
	this->size_move_emotion = quantity;
	for(int i=0;i<quantity;++i){
		this->move_emotional_distance[i] = distance[i];
		this->move_emotional_velocity[i] = velocity[i];
	}
	//TODO set move_x = vector_x;
	generateEmotionalActionMove();
	generateEmotionalVelocityMove();
}*/


/*void BodyController::setEmotionalOscillateBody(bool repeat, int quantity, float distance[],float velocity[]){
	this->repeat_oscillation = repeat;
	this->pos_oscillate_yaw = 0;
	this->size_oscillate_emotion = quantity;
	for(int i=0;i<quantity;++i){
		this->oscillate_emotional_distance[i] = distance[i];
		this->oscillate_emotional_velocity[i] = velocity[i];
	}
	//TODO set oscillate_x = vector_x;
	if(!is_oscillating){
		is_oscillating_emotional = true;
		generateEmotionalActionOscillate();
	}
	generateEmotionalVelocityOscillate();
}*/

/*void BodyController::generateEmotionalVelocityOscillate(){
	if(size_oscillate_emotion>0){
		velocity_oscillate_yaw = (oscillate_emotional_velocity[pos_oscillate_yaw]);
	}else{
		velocity_oscillate_yaw = angular_velocity;
	}
}*/

void BodyController::setOscillateVelocity(float velocity_yaw){
	velocity_oscillate_yaw = velocity_yaw;
}
bool BodyController::getHasArrive(){
	return has_arrived;
}


void BodyController::setHasArrive(bool arrive){
	this->has_arrived = arrive;
}
bool BodyController::controll(float position_x, float position_y, float position_theata){
	bool temp = true;	
	if(is_moving /*|| is_moving_emotional*/){
		/*if(is_moving_emotional){
			if(emotional_distance<(current_distance-initial_emotional_distance)){
				initial_emotional_distance = current_distance;
				move_emotion_synch = true;
			}
		}*/
		if(!has_arrived){
			this->calculateLinearVelocity(position_x,position_y,position_theata);
			if(is_reducing_velocity&&is_moving){
				is_oscillating = false;
				//is_oscillating_emotional = false;
			}
			has_arrived = has_arrived_linear;
			if(!(is_oscillating/*||is_oscillating_emotional*/)){
				calculateAngularVelocity(position_theata);
				has_arrived = has_arrived_linear & has_arrived_angular;
			}
		} else{
			is_moving = false;
			//is_moving_emotional = false;
		}
		temp = false;
	}
	if(is_oscillating/*||is_oscillating_emotional*/){
		if(desire_angle_to_oscillate_yaw != 0){
			desire_velocity_theta = this->updateOscillation(velocity_oscillate_yaw,position_theata,desire_theta,desire_angle_to_oscillate_yaw,yaw_error,&forward_direction_yaw);
			temp = false;
		}
	}
	return temp;
}


void BodyController::calculateAngularVelocity(float position_theta){
	float distance_theta = desire_theta - position_theta;
	distance_theta = correctAngle(distance_theta);
	if(fabs(distance_theta)<reduce_angular_velocity){
		desire_velocity_theta = velocity_oscillate_yaw*distance_theta/reduce_angular_velocity;
	}else{
		desire_velocity_theta = velocity_oscillate_yaw*signum(distance_theta);
	}
	if(fabs(distance_theta)<yaw_error){
		desire_velocity_theta = 0.0;
		has_arrived_angular = true;
	}
}
void BodyController::calculateLinearVelocity(float position_x, float position_y, float position_theata){
	current_distance = current_distance+ sqrtf(powf(position_x-last_position_x,2.0)+powf(position_y-last_position_y,2.0));
	last_position_x = position_x;
	last_position_y = position_y;
	//Change the reference frame
	float x_temp = this->desire_x-position_x;
	float y_temp = this->desire_y-position_y;
	bool temp_is_reducing_x, temp_is_reducing_y;
	//Verification if it should stop the x velocity
	if(fabs(x_temp)<reduce_linear_velocity){
		temp_is_reducing_x = true;
		desire_velocity_x = static_cast<float>((current_linear_velocity*x_temp)/reduce_linear_velocity);
	}else{
		temp_is_reducing_x = false;
		desire_velocity_x = static_cast<float>(current_linear_velocity*signum(x_temp));
	}
	//Verification if it should stop the y velocity
	if(fabs(y_temp)<reduce_linear_velocity){
		temp_is_reducing_y = true;
		desire_velocity_y = static_cast<float>((current_linear_velocity*y_temp)/reduce_linear_velocity);
	}else{
		temp_is_reducing_y = false;
		desire_velocity_y = static_cast<float>(current_linear_velocity*signum(y_temp));
	}
	float temp_vel_x = cosf(position_theata)*desire_velocity_x+sinf(position_theata)*desire_velocity_y;
	float temp_vel_y = cosf(position_theata)*desire_velocity_y-sinf(position_theata)*desire_velocity_x;
	desire_velocity_x = temp_vel_x;	
	desire_velocity_y = temp_vel_y;
	is_reducing_velocity = temp_is_reducing_x && temp_is_reducing_y;
	if(fabs(x_temp)<x_error&&fabs(y_temp)<y_error){
		has_arrived_linear = true;
		desire_velocity_x = 0.0;
		desire_velocity_y = 0.0;
	}
}

float BodyController::signum(float num){
	if(num<0)
		return -1;
	return 1;
}

float BodyController::correctAngle(float distance_theta){
	if(distance_theta>M_PI){
		distance_theta= distance_theta-2.0*M_PI;
	}else if(distance_theta<-M_PI){
		distance_theta = distance_theta+2.0*M_PI;
	}
	return distance_theta;
}

float BodyController::fabs(float num){
	if(num<0)
		return -1*num;
	return num;
}

float BodyController::updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction){
	float distance_theta = current_angle - desire_angle_to_move;
	float temp_velocity = desire_velocity;
	verifyAngle(&distance_theta);
	if(*forward_direction){
		if(distance_theta>=desire_angle_to_oscillate){
			*forward_direction = !*forward_direction;
			return -1.0*temp_velocity;
		}
	} else{
		temp_velocity = -1.0*temp_velocity;
		if(distance_theta<=(-1.0*desire_angle_to_oscillate)){
			*forward_direction = !*forward_direction;
			return -1.0*temp_velocity;
		}
	}
	return temp_velocity;
}
