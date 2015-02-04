/*
 * TestLoadEmotion.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#define DEBUG_C_PLUS_PLUS

#include <typeinfo>
#include "boost/shared_ptr.hpp"
#include "../Parameters/Parameter.h"
#include "../Parameters/EmotionalParameters/EmotionMovementParameter.h"
#include "../EmotionDescription/ActionChanges.h"
#include "../EmotionDescription/EmotionProfile.h"
#include "../LoadInformation/EmotionalLoad.h"
#include "../Parsers/ParserAction.h"
#include "../ActionModulation/ActionAddition.h"
#include "../ActionDescription/SimpleActions/SimpleActionDoNothing.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionSpeak.h"
#include "../ActionDescription/CompositeActions/CompositeActionWalk.h"
#include "../ActionModulation/ActionModulationSubSystem.h"
#include "../LoadInformation/CharacterPaceLoad.h"
#include "../Parsers/ParserActionParameters.h"
#include "../Parsers/EmotionParser.h"
#include "../Parameters/MovementParameters/TypePosition.h"
#include "../Parameters/MovementParameters/Position.h"
#include "../Parameters/MovementParameters/Point.h"
#include "../Parameters/MovementParameters/Landmark.h"
#include "../Parameters/MovementParameters/Square.h"
#include "../Parameters/MovementParameters/Circle.h"

void testActionChanges();
void testLoadEmotions();
void testFindSubString();
void testParserActions();
void testActionAddition();
void testActionSubSystem();
void testActionSubSystemActionModulation();
void testCharacterEmotionDescription();
void testNewProblems();
void printContext(AbstractContextDescription *context);
void printMessages(ActionModulationSubSystem *action_sub_system);
void printEmotionMessages(ActionModulationSubSystem *action_sub_system);
void printListToStop(std::vector<std::string> list);
std::map<std::string,AbstractActionDescription * > loadAvailableAction();
void testActionMessages();
void testEmptyMessage();
void testEmotionParser();
void testSynchProblems();
void testPositionParameter();
bool parserJSON(std::string parameter, boost::shared_ptr<Position> *result, TypePosition *type_position_parameter);
int main(){
	//testPositionParameter();
	testSynchProblems();
	//testEmotionParser();
	//testEmptyMessage();
	//testActionMessages();
	//testNewProblems();
	//testActionSubSystemActionModulation();
	//testCharacterEmotionDescription();
	//testActionSubSystem();
	//testActionAddition();
	//testParserActions();
	//testFindSubString();
	//testLoadEmotions();
	//testActionChanges();
	return 0;
}


bool parserJSON(std::string parameter, boost::shared_ptr<Position> *result, TypePosition *type_position_parameter){
	Json::Reader reader;
	Json::Value root;
	bool parsing_successful = reader.parse(parameter, root, false);
	if(parsing_successful){
		Json::Value temp_info = root.get("name","UTF-8");
		if(temp_info.asString().compare("parameter_point") == 0){
			*type_position_parameter = PointPosition;
			boost::shared_ptr<Point> point_parameter(new Point);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("pose","UTF-8");
				if(!temp_info.isNull() && temp_info.isArray()){
					point_parameter->setHasPose(true);
					std::vector<float> numbers;
					for(int i = 0; i<temp_info.size(); ++i){
						numbers.push_back(temp_info[i].asFloat());
					}
					if(numbers.size()==4){
						point_parameter->setQuaternionX(numbers.at(0));
						point_parameter->setQuaternionY(numbers.at(1));
						point_parameter->setQuaternionZ(numbers.at(2));
						point_parameter->setQuaternionW(numbers.at(3));
					}
				}else{
					point_parameter->setHasPose(false);
				}
				*result = point_parameter;
				return true;
			}
		}else if(temp_info.asString().compare("parameter_landmark") == 0 ){
			*type_position_parameter = LandmarkPosition;
			boost::shared_ptr<Landmark> landmark_parameter(new Landmark);
			temp_info = root.get("landmark_id","UTF-8");
			if(!temp_info.isNull() && temp_info.isNumeric()){
				landmark_parameter->setIdLandmakr(temp_info.asInt());
				temp_info = root.get("landmark_type","UTF-8");
				if(!temp_info.isNull() && temp_info.isString()){
					if(temp_info.asString().compare("Person_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Person_Landmark);
					}else if(temp_info.asString().compare("Object_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Object_Landmark);
					}else if(temp_info.asString().compare("Place_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Place_Landmark);
					}
					temp_info = root.get("pose","UTF-8");
					if(!temp_info.isNull() && temp_info.isArray()){
						landmark_parameter->setHasPose(true);
						std::vector<float> numbers;
						for(int i = 0; i<temp_info.size(); ++i){
							numbers.push_back(temp_info[i].asFloat());
						}
						if(numbers.size()==4){
							landmark_parameter->setQuaternionX(numbers.at(0));
							landmark_parameter->setQuaternionY(numbers.at(1));
							landmark_parameter->setQuaternionZ(numbers.at(2));
							landmark_parameter->setQuaternionW(numbers.at(3));
						}
					}else{
						landmark_parameter->setHasPose(false);
					}
					*result = landmark_parameter;
					return true;
				}
			}
		}else if(temp_info.asString().compare("parameter_circle") == 0 ){
			*type_position_parameter = CirclePosition;
			boost::shared_ptr<Circle> point_parameter(new Circle);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("radio","UTF-8");
				if(!temp_info.isNull() && temp_info.isNumeric()){
					point_parameter->setRadio(temp_info.asFloat());
					temp_info = root.get("pose","UTF-8");
					if(!temp_info.isNull() && temp_info.isArray()){
						point_parameter->setHasPose(true);
						std::vector<float> numbers;
						for(int i = 0; i<temp_info.size(); ++i){
							numbers.push_back(temp_info[i].asFloat());
						}
						if(numbers.size()==4){
							point_parameter->setQuaternionX(numbers.at(0));
							point_parameter->setQuaternionY(numbers.at(1));
							point_parameter->setQuaternionZ(numbers.at(2));
							point_parameter->setQuaternionW(numbers.at(3));
						}
					}else{
						point_parameter->setHasPose(false);
					}
				}
				*result = point_parameter;
				return true;
			}
		}else if(temp_info.asString().compare("parameter_square") == 0 ){
			*type_position_parameter = SquarePosition;
			boost::shared_ptr<Square> point_parameter(new Square);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("delta","UTF-8");
				if(!temp_info.isNull() && temp_info.isArray()){
					std::vector<float> delta;
					for(int i = 0; i<temp_info.size(); ++i){
						delta.push_back(temp_info[i].asFloat());
					}
					if(delta.size()==2){
						point_parameter->setDeltaX(delta.at(0));
						point_parameter->setDeltaY(delta.at(0));
						temp_info = root.get("pose","UTF-8");
						if(!temp_info.isNull() && temp_info.isArray()){
							point_parameter->setHasPose(true);
							std::vector<float> numbers;
							for(int i = 0; i<temp_info.size(); ++i){
								numbers.push_back(temp_info[i].asFloat());
							}
							if(numbers.size()==4){
								point_parameter->setQuaternionX(numbers.at(0));
								point_parameter->setQuaternionY(numbers.at(1));
								point_parameter->setQuaternionZ(numbers.at(2));
								point_parameter->setQuaternionW(numbers.at(3));
							}
						}else{
							point_parameter->setHasPose(false);
						}
					}
				}
				*result = point_parameter;
				return true;
			}
		}
	}
	return false;
}


void testPositionParameter(){
	//std::string message = "{\"name\":\"parameter_point\",\"point\":[0.6,0,0],\"pose\":[0,0,0,1],\"type\":\"mandatory_parameter\"}";
	std::string message = "{\"name\":\"parameter_landmark\",\"landmark_id\":1,\"landmark_type\":\"Person_Landmark\",\"pose\":[0,0,0,1],\"type\":\"mandatory_parameter\"}";
	boost::shared_ptr<Position> temp_position;
	TypePosition type;
	bool works = parserJSON(message,&temp_position,&type);
	std::cout<<" It worked "<<(works?"yes ":"no ")<<(temp_position->getHasPose()?"yes ":"no ")<< temp_position->getQuaterionW()<<std::endl;
}

void testEmotionParser(){
	std::vector<EmotionMovementParameter> emotion_vector_x,emotion_vector_y,emotion_vector_z;
	bool repetition, it_work;
	std::string message = "{\"type\":\"movement_parameter\",\"repetition \" : \"no\",\"parameters\": [[{\"space\":0.6236000061035156,\"velocity\":1},{\"space\":0.6236000061035156,\"velocity\":1}],[{\"space\":0.6236000061035156,\"velocity\":1}],[{\"space\":0.6236000061035156,\"velocity\":1}]]}";
	std::cout<<message<<std::endl;
	EmotionParser parser;
	it_work = parser.parse(message,&emotion_vector_x,&emotion_vector_y,&emotion_vector_z,&repetition);
	std::cout<<emotion_vector_x.size()<<" "<<emotion_vector_y.size()<<" "<<emotion_vector_z.size()<<std::endl;
}

void testEmptyMessage(){
	Json::Reader reader;
	Json::Value root, temp;
	bool parsing_successful = reader.parse("{ \"a\":1}", root, false);
	if(parsing_successful){
		std::cout<<"Ok"<<std::endl;
		if(root.empty()){
			std::cout<<"Is empty"<<std::endl;
		}
	}

}

void testActionMessages(){
	ParserActionParameters parser;
	parser.parser(" {\"amplitude\":[0,0,0,0],\"name\":\"parameter_amplitude\",\"type\":\"mandatory_parameter\"}");
}

void printListToStop(std::vector<std::string> list){
	std::cout<<"actions to finish: ";
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
		std::cout<<*it<<" "<<std::endl;
	}
	std::cout<<std::endl;
}

void printMessages(ActionModulationSubSystem *action_sub_system){
	std::map<std::string,std::string> list_message_actions = action_sub_system->generateParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		std::cout<<"Sending Action "<<it->first.c_str()<<"- "<<it->second.c_str()<<std::endl;
	}
}


void printEmotionMessages(ActionModulationSubSystem *action_sub_system){
	std::map<std::string,std::string> list_message_actions = action_sub_system->generateEmotionalParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		std::cout<<"Sending Emotions "<<it->first.c_str()<<"- "<<it->second.c_str()<<std::endl;
	}
}


void testSynchProblems(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string path_name_character = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_move_torso.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/parallel_action_keepon_test_1.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/keepon_test_2.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.setPathCharacterPace(path_name_character);
		action_sub_system.loadInformation();
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		printListToStop(action_sub_system.actiosToStop());
		printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		std::vector<std::string> list = action_sub_system.actionSynchronization("move_body");
		for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
			std::cout<<"Action.. "<<*it<<std::endl;
		}
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy 0.2"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",0.2);
		printListToStop(action_sub_system.actiosToStop());
		printEmotionMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		action_sub_system.clearListNewAction();
		std::cout<<"Action Synch move_torso"<<std::endl;
		list = action_sub_system.actionSynchronization("move_torso");
		std::map<std::string,std::string> new_list = action_sub_system.getListNewAction();
		for(std::map<std::string,std::string>::iterator it = new_list.begin(); it  != new_list.end(); ++it){
			std::cout<<it->first<<" "<<it->second<<std::endl;
		}
		for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
			std::cout<<"Action.. "<<*it<<std::endl;
		}
		action_sub_system.printContext(action_sub_system.getContext());
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Emotional synch do_nothing"<<std::endl;
		list = action_sub_system.emotionSynchronization("do_nothing");
		for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
			std::cout<<"Emotion .. "<<*it<<std::endl;
		}
		/*printEmotionMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;*/
	}
}
void testNewProblems(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string path_name_character = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.setPathCharacterPace(path_name_character);
		action_sub_system.loadInformation();
		std::cout<<message<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		printListToStop(action_sub_system.actiosToStop());
		//printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		printListToStop(action_sub_system.actiosToStop());
		printEmotionMessages(&action_sub_system);
		//printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy 1"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		printListToStop(action_sub_system.actiosToStop());
		printEmotionMessages(&action_sub_system);
		//printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion sad 0"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",0);
		printListToStop(action_sub_system.actiosToStop());
		printEmotionMessages(&action_sub_system);
		//printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion angry 0.1"<<std::endl;
		action_sub_system.callBackNewEmotion("angry",0.1);
		printListToStop(action_sub_system.actiosToStop());
		printEmotionMessages(&action_sub_system);
		//printMessages(&action_sub_system);
		std::cout<<"----------------------"<<std::endl;
		file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
		std::ifstream test2(file.c_str(), std::ifstream::binary);
		std::string message2((std::istreambuf_iterator<char>(test2)), std::istreambuf_iterator<char>());
		std::cout<<"Testing action message2"<<std::endl;
		action_sub_system.callBackNewAction(message2);
		printListToStop(action_sub_system.actiosToStop());
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message xxx"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message xx"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message x"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"----------------------"<<std::endl;
	}

}
void testActionSubSystemActionModulation(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string path_name_character = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/test_action.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.setPathCharacterPace(path_name_character);
		action_sub_system.loadInformation();
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction("stop 1");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction("stop");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion sad"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		std::vector<std::string> list = action_sub_system.actionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion 2"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion 3"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion 4"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action oscilalte_body"<<std::endl;
		action_sub_system.actionSynchronization("oscillate_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_torso");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("speak");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing intensity happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",0.5);
		std::cout<<"Testing emotion sad"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing emotion and intensity content"<<std::endl;
		action_sub_system.callBackNewEmotion("content",0.5);
		file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
		std::ifstream test2(file.c_str(), std::ifstream::binary);
		std::string message2((std::istreambuf_iterator<char>(test2)), std::istreambuf_iterator<char>());
		std::cout<<"Testing action message2"<<std::endl;
		action_sub_system.callBackNewAction(message2);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("speak");
	}
}

void testActionSubSystem(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.loadInformation();
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		std::cout<<"Testing intensity happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",0.5);
		std::cout<<"Testing emotion sad"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing emotion and intensity content"<<std::endl;
		action_sub_system.callBackNewEmotion("content",0.5);
		file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
		std::ifstream test2(file.c_str(), std::ifstream::binary);
		std::string message2((std::istreambuf_iterator<char>(test2)), std::istreambuf_iterator<char>());
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message2);
	}
}

void testCharacterEmotionDescription(){
	std::string path_name = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	CharacterPaceLoad character_pace_load;
	character_pace_load.setDirectoryPath(path_name);
	character_pace_load.LoadInformation();
	std::map<std::string, CharacterEmotionModification *> temp = character_pace_load.getCharacterMovementInformation();
	std::cout<<"aaa"<<std::endl;
	for(std::map<std::string, CharacterEmotionModification *>::iterator it = temp.begin(); it != temp.end(); ++it){
		delete it->second;
	}
}

void testActionAddition(){
	ActionAddition action_addition;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_addition.setPathName(path_name);
		action_addition.loadEmotions();
		action_addition.loadEmotions();
		AbstractContextDescription *context = action_addition.addAdditionalActions(message,"happy");
		printContext(context);
		std::cout<<"Ready"<<std::endl;
		if (test.good()) {
			std::cout<<"So far so good"<<std::endl;
			action_addition.changeEmotionalAction(&context,"sad");
			std::cout<<"New context"<<std::endl;
			printContext(context);
		}
		delete context;
	}
}
void testParserActions(){
	ParserAction  parserAction;
	std::map<std::string,AbstractActionDescription * >  actions = loadAvailableAction();
	parserAction.setActionsAvailable(&actions);
	/*std::string message1 = "{\"type\": \"simple_action\","
	"\"name\": \"move_body\","
	"\"parameters\":"
	"["
	"		{"
	"			\"type\"		:	\"mandatory_parameter\","
	"			\"name\"		:	\"parameter_point\","
	"			\"pose\" 		:	[0,0,0,1],"
	"			\"point\" 	:	[0,0,0]"
	"		}"
	"]"
	"}";*/
	//std::string file = "/media/julian/Julian/workspace-cpp/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/media/julian/Julian/workspace-cpp/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		AbstractContextDescription *context  = parserAction.parser(message);
		printContext(context);
		delete context;
	}
	for(std::map<std::string,AbstractActionDescription *>::iterator it = actions.begin();
			it !=actions.end();++it){
		delete it->second;
	}
	//std::cout<<message<<std::endl;
}


void printContext(AbstractContextDescription *context){
	if(context!=0){
		std::cout<<"context name: "<<typeid(*context).name()<<std::endl;
		if(typeid(*context).name()==typeid(CompositeContextDescription).name()){
			CompositeContextDescription * temp_context = static_cast<CompositeContextDescription *>(context);
			std::cout<<"*****************"<<std::endl;
			std::cout<<"Context-action synch: "<<temp_context->getActionsSynch()<<", type: "<<temp_context->getContextType()
					<<", emotion synch:"<<temp_context->getEmotionalSynch()<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::vector<AbstractContextDescription *> temp_sub_context = temp_context->getSubContext();
			std::cout<<"---------------"<<std::endl;
			for(std::vector<AbstractContextDescription *>::iterator it = temp_sub_context.begin();
					it != temp_sub_context.end(); ++it){
					printContext(*it);
				std::cout<<"---------------"<<std::endl;
			}
			std::cout<<"*****************"<<std::endl;
		}else if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
			SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(context);
			std::cout<<"Action - name: "<<temp_context->getActionName()<<", emotional "<<temp_context->getIsEmotional()<<", parameters: "<<temp_context->getActionParameters()
					<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::vector<EmotionParameter *> temp_pameter_emotion = temp_context->getEmotionChanges().getVectorParameters();
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				EmotionMovementParameter *temp_movement = static_cast<EmotionMovementParameter *>((*it_emotion));
				std::cout<<"Parameter timing "<<temp_movement->getEmotionParameterTime()<<" parameter spacing "<<temp_movement->getEmotionParameterSpacing()<<std::endl;
			}
		}
	}
}

std::map<std::string,AbstractActionDescription * > loadAvailableAction(){

	std::map<std::string,AbstractActionDescription * > actions;
	SimpleActionDoNothing *action_do_nothing = new SimpleActionDoNothing;
	actions[action_do_nothing->getActionName()] = action_do_nothing;
	SimpleActionMoveBody *action_move_body = new SimpleActionMoveBody;
	actions[action_move_body->getActionName()] = action_move_body;
	SimpleActionMoveShoulder *action_move_shoulder = new SimpleActionMoveShoulder;
	actions[action_move_shoulder->getActionName()] = action_move_shoulder;
	SimpleActionMoveTorso *action_move_torso = new SimpleActionMoveTorso;
	actions[action_move_torso->getActionName()] = action_move_torso;
	SimpleActionOscillateBody *action_oscillate_body = new SimpleActionOscillateBody;
	actions[action_oscillate_body->getActionName()] = action_oscillate_body;
	SimpleActionOscillateShoulder *action_oscillate_shoulder = new SimpleActionOscillateShoulder;
	actions[action_oscillate_shoulder->getActionName()] = action_oscillate_shoulder;
	SimpleActionOscillateTorso *action_oscillate_torso = new SimpleActionOscillateTorso;
	actions[action_oscillate_torso->getActionName()] = action_oscillate_torso;
	SimpleActionSpeak *action_speak = new SimpleActionSpeak;
	actions[action_speak->getActionName()] = action_speak;
	CompositeActionWalk *action_walk = new CompositeActionWalk;
	actions[action_walk->getActionName()] = action_walk;

	return actions;
}

void testFindSubString(){
	std::string temp = "parameter_point_body";
	int occurence = temp.find("__bod");
	std::cout<<occurence<<" - "<<temp.size()<<std::endl;
	std::string temp2 = temp.substr(0,occurence);
	std::cout<<"result: "<<temp2<<std::endl;
}
//Test load of emotions
void testLoadEmotions(){
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	EmotionalLoad emotion_load;
	emotion_load.setDirectoryPath(path_name);
	emotion_load.LoadInformation();
	std::map<string, EmotionProfile *> emotions_available = emotion_load.getEmotionsAvailable();
	std::cout<<"Finish to load, the actions loaded are:"<<std::endl;
	for(std::map<string, EmotionProfile *>::iterator it = emotions_available.begin(); it != emotions_available.end();
			it++){
		std::cout<<"Emotion: "<<it->first<<std::endl;
		std::cout<<"Info Profile, Emotion: "<<it->second->getEmotionProfileEmotion()<<
				" Action: "<<it->second->getEmotionProfileAction()<<" ??? "<<it->second->getEmotionProfileName()<<std::endl;
		std::vector<ActionChanges *> temp = it->second->getActionChanges();
		for(std::vector<ActionChanges *>::iterator it_t = temp.begin();
				it_t != temp.end(); ++it_t){
			std::cout<<"Action changes: "<<(*it_t)->getActionThatModyfies()<<std::endl;
		}
		delete it->second;
	}
}

//Test the creation and delete of emotion profile
void testActionChanges(){
	EmotionProfile * emotion = new EmotionProfile();
	ActionChanges * action = new ActionChanges();
	EmotionMovementParameter *test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	emotion->addActionChanges(action);
	action = new ActionChanges();
	test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		emotion->addActionChanges(action);
	delete emotion;
}
