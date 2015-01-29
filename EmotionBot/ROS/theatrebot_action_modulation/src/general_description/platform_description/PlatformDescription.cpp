/*
 * PlatformDescription.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#include "PlatformDescription.h"

PlatformDescription::PlatformDescription() {
	// TODO Auto-generated constructor stub

}

PlatformDescription::~PlatformDescription() {
	// TODO Auto-generated destructor stub
}

/*map<string, shared_ptr<PlatformActionDescription>string >*/
map <string,string> PlatformDescription::getSimpleActionsAvailable(){
	return this->simple_actions_available;
}

void PlatformDescription::setSimpleActionsAvailable(
		map <string,string> simple_actions_available
/*map<string, shared_ptr<PlatformActionDescription>string > simple_actions_available*/){
	this->simple_actions_available = simple_actions_available;
}

void PlatformDescription::addSimpleActionAvailable(string simple_action/*,shared_ptr<PlatformActionDescription> parameter*/){
	this->simple_actions_available[simple_action]=simple_action;/*parameter*/
}
void PlatformDescription::setPlatformName(string platform_name){
	this->platform_name = platform_name;
}
string PlatformDescription::getPlatformName(){
	return platform_name;
}

