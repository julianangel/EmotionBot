/*
 * ActionModulation.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 */

#include "ActionModulation.h"

ActionModulation::ActionModulation() {

}

ActionModulation::~ActionModulation() {
	for(std::map<std::string, CharacterEmotionModification *>::iterator it = modifications_available.begin();
			it != modifications_available.end(); ++it){
		delete it->second;
	}
}


void ActionModulation::setPathCharacterModifications(std::string path){
	this->path_name = path;
}

void ActionModulation::actionModulation(AbstractContextDescription * context, std::string emotion, float intensity){
	if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
		SimpleContextDescription * temp_simple_context = static_cast<SimpleContextDescription *>(context);
		//Modify Parameters and safe it in the string, without using
		this->modifyParameters(temp_simple_context,emotion,intensity);
	} else if(typeid(*context).name() == typeid(CompositeContextDescription).name()){
		CompositeContextDescription * temp_composite_action = static_cast<CompositeContextDescription *>(context);
		std::vector<AbstractContextDescription *>  next_context = temp_composite_action->getSubContext();
		for(unsigned int i = 0; i < next_context.size(); ++i){
			this->actionModulation((next_context.at(i)),emotion,intensity);
		}
	}else{
		//TODO send error message
	}
}


void ActionModulation::loadCharacterModification(){
	CharacterPaceLoad character_load;
	if(this->modifications_available.size() != 0){
		for(std::map<std::string, CharacterEmotionModification *>::iterator it = modifications_available.begin();
				it != modifications_available.end();
				++it){
			delete it->second;
		}
	}
	character_load.setDirectoryPath(this->path_name);
	character_load.LoadInformation();
	modifications_available = character_load.getCharacterMovementInformation();
}

/*
 * This method modifies the parameters and save the changes in the string.
 * This method should not modify save the changes in the parameters!
 */
void ActionModulation::modifyParameters(SimpleContextDescription* simple_context, std::string emotion, float intensity){
	ActionChanges temp_action_change = simple_context->getEmotionChanges();
	//std::cout<<"aaa "<< temp_action_change.getVectorParameters().at(0)<<std::endl;
	std::string message = "{";
	if(intensity == 0){
		simple_context->cleanEmotionParameters();
	}else{
		std::vector<EmotionParameter *> temp_pameter_emotion = temp_action_change.getVectorParameters();
		float reference_character_action;
		if(temp_pameter_emotion.size()>0){
			//Get the default values if there is not information
			bool default_values = true;
			std::map<std::string, CharacterMovementModification *> * temp_modification = 0;
			std::map<std::string,CharacterEmotionModification * >::iterator character_profile = modifications_available.find(emotion);
			if(character_profile != modifications_available.end()){
				default_values = false;
				temp_modification = character_profile->second->getEmotionModification();
			}
			message +="\"type\":\"movement_parameter\",";
			message +="\"repetition\" : ";
			message += (temp_action_change.getRepetition()?"\"yes\",":"\"no\",");
			//message += "\"reference \" :";
			//message += temp_action_change.g
			bool first_parameter = true;
			//Factor to modify
			float modifier = 1.0/(1.0+std::exp(6.0-12.0*intensity));
			message += "\"parameters\": [[";
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				if(!first_parameter){
					message += ",";
				}
				if(default_values && (typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name())){
					message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference());
					reference_character_action = temp_action_change.getReference();
				}else if(typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name()){
					std::map<std::string, CharacterMovementModification *>::iterator character_action_change = temp_modification->find(simple_context->getActionName());
					if(character_action_change != temp_modification->end()){
						CharacterMovementModification * temp_character = character_action_change->second;
						message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference(),temp_character,simple_context->getIsEmotional());
						reference_character_action = temp_character->getBias();
					}
				}
				first_parameter = false;
			}
			message += "]";
			if(temp_action_change.getVectorParametersZ().size()==0){
				message += "],";
				message += "\"reference\" :";
			    std::ostringstream buff;
			    buff<<reference_character_action;
				message += buff.str();
			}
		}temp_pameter_emotion = temp_action_change.getVectorParametersY();
		if(temp_pameter_emotion.size()>0){
			//Get the default values if there is not information
			bool default_values = true;
			std::map<std::string, CharacterMovementModification *> * temp_modification = 0;
			std::map<std::string,CharacterEmotionModification * >::iterator character_profile = modifications_available.find(emotion);
			if(character_profile != modifications_available.end()){
				default_values = false;
				temp_modification = character_profile->second->getEmotionModification();
			}
			bool first_parameter = true;
			//Factor to modify
			float modifier = 1.0/(1.0+std::exp(6.0-12.0*intensity));
			message += ",[";
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				if(!first_parameter){
					message += ",";
				}
				if(default_values && (typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name())){
					message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference());
				}else if(typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name()){
					std::map<std::string, CharacterMovementModification *>::iterator character_action_change = temp_modification->find(simple_context->getActionName());
					if(character_action_change != temp_modification->end()){
						CharacterMovementModification * temp_character = character_action_change->second;
						message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference(),temp_character,simple_context->getIsEmotional());
					}
				}
				first_parameter = false;
			}
			message += "]";
		}temp_pameter_emotion = temp_action_change.getVectorParametersZ();
		if(temp_pameter_emotion.size()>0){
			//Get the default values if there is not information
			bool default_values = true;
			std::map<std::string, CharacterMovementModification *> * temp_modification = 0;
			std::map<std::string,CharacterEmotionModification * >::iterator character_profile = modifications_available.find(emotion);
			if(character_profile != modifications_available.end()){
				default_values = false;
				temp_modification = character_profile->second->getEmotionModification();
			}
			bool first_parameter = true;
			//Factor to modify
			float modifier = 1.0/(1.0+std::exp(6.0-12.0*intensity));
			message += ",[";
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				if(!first_parameter){
					message += ",";
				}
				if(default_values && (typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name())){
					message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference());
				}else if(typeid(**it_emotion).name()==typeid(EmotionMovementParameter).name()){
					std::map<std::string, CharacterMovementModification *>::iterator character_action_change = temp_modification->find(simple_context->getActionName());
					if(character_action_change != temp_modification->end()){
						CharacterMovementModification * temp_character = character_action_change->second;
						message += this->modifyMovementParameters(static_cast<EmotionMovementParameter *>(*it_emotion),emotion,modifier,temp_action_change.getReference(),temp_character,simple_context->getIsEmotional());
					}
				}
				first_parameter = false;
			}
			message += "]],";
			message += "\"reference\" :";
		    std::ostringstream buff;
		    buff<<reference_character_action;
			message += buff.str();
		}
	}
	message += "}";
	simple_context->setEmotionalParameterMessage(message);
}

/*
 * This method modulates the parameters that are related to movement
 * This method should not modify save the changes in the parameters!
 */
std::string ActionModulation::modifyMovementParameters(EmotionMovementParameter * emotion_parameter, std::string emotion, float modifier, float reference){
	EmotionMovementParameter parameter = *emotion_parameter;
	//Modify parameters using the variable parameter modifier
	parameter.setEmotionParameterSpacing(parameter.getEmotionParameterSpacing());
	float velocity = parameter.getEmotionParameterTime();
	if(velocity != 0){
		velocity  = (parameter.getEmotionParameterSpacing()/velocity-reference)*modifier;
		velocity += reference;
		velocity = absFloat(velocity);
	}else{
		velocity = 0;
	}
	parameter.setEmotionParameterTime(velocity);
	//Return message
	return parameter.generateMessage();
}


std::string ActionModulation::modifyMovementParameters(EmotionMovementParameter * emotion_parameter, std::string emotion, float modifier, float reference,CharacterMovementModification * temp_character, bool is_emotional){
	EmotionMovementParameter parameter = *emotion_parameter;
	float spacing  = parameter.getEmotionParameterSpacing()*temp_character->getLongness();
	float velocity = parameter.getEmotionParameterTime();
	if(velocity != 0.0){
		//std::cout<<"Velocity before anything: "<<(spacing/velocity)<<" Reference: "<<(reference)<<" Character bias: "<<temp_character->getBias()<<std::endl;
		//velocity = (((spacing/velocity)*temp_character->getBias())/reference)*modifier*temp_character->getAmplitude();
		velocity = (((spacing/velocity)-reference)/reference*modifier*temp_character->getAmplitude()*temp_character->getBias())+temp_character->getBias();
		if(is_emotional){
			velocity = velocity * modifier;
		}
		//std::cout<<"Final velocity "<<velocity<<std::endl;
		//velocity += temp_character->getBias();
		velocity = absFloat(velocity);
	}else{
		velocity = 0.0;
	}
	parameter.setEmotionParameterSpacing(spacing);
	parameter.setEmotionParameterTime(velocity);
	return parameter.generateMessage();
}
