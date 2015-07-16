#ifndef BodyController_H_
#define BodyController_H_

#define M_PI 3.1415926535897932384626433832795


#include <math.h>

class BodyController{

public:
	BodyController();
	~BodyController();
	void OscillateBodyAction(float yaw);
	void stopMoveBodyAction();
	void stopOscillateBodyAction();
	void synchEmotionMove();
	void synchEmotionOscillate();
	void setEmotionalMoveBody(bool repeat, int quantity, float distance[],float velocity[]);
	void setEmotionalOscillateBody(bool repeat, int quantity, float distance[],float velocity[]);
	void MoveBodyAction(float position_x,float position_y, float position_theta);
	void setVelocity(float linear, float angular);
	bool controll(float position_x, float position_y, float position_theata);
	bool getEmotionalSynch();
	void setEmotionalSynch(bool set_value);
	bool getHasArrive();
	void setHasArrive(bool arrive);
	float getDesireVelocityX();
	float getDesireVelocityY();
	float getDesireVelocityTheta();

private:
	/*
	* Movement variables
	*/
	bool is_moving;
	float x_error;
	float y_error;
	float reduce_linear_velocity;
	float linear_velocity;
	bool has_arrived;
	bool has_arrived_linear;
	bool has_arrived_angular;
	float maximum_linear_velocity;
	float current_linear_velocity;
	float current_distance;
	float desire_x;
	float desire_y;
	float desire_theta;
	bool is_reducing_velocity;
	/*
	* Oscillation Variables	
	*/
	bool is_oscillating;
	float yaw_error;
	float angular_velocity;
	float reduce_angular_velocity;
	float maximum_error_theta;
	float maximum_angular_velocity;
	float desire_angle_to_oscillate_yaw;
	float velocity_oscillate_yaw;
	bool forward_direction_yaw;
	/*
	* Movement emotional variables
	*/	
	bool repeat_move;
	bool is_moving_emotional;
	float emotional_distance;
	float initial_emotional_distance;
	int pos_move;
	bool move_emotion_synch;
	int max_size;
	int size_move_emotion;
	float move_emotional_distance[15];
	float move_emotional_velocity[15];

	/*
	* Oscillation emotional variables
	*/
	bool is_oscillating_emotional;
	bool repeat_oscillation;
	int pos_oscillate_yaw;
	int size_oscillate_emotion;
	float oscillate_emotional_distance[15];
	float oscillate_emotional_velocity[15];
	
	//Temporal variables necessary to the system
	float last_position_x;
	float last_position_y;
	/*
	 * Control velocities
	 */
	float desire_velocity_x;
	float desire_velocity_y;
	float desire_velocity_theta;
	/*
	*Methods	
	*/
	void generateEmotionalActionMove();
	void generateEmotionalVelocityMove();
	void verifyAngle(float *angle);
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void calculateLinearVelocity(float position_x, float position_y, float position_theata);
	void calculateAngularVelocity(float position_theta);
	float correctAngle(float distance_theta);
	float updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	float fabs(float num);
	float signum(float num);

};
#endif /* BodyController_H_ */
