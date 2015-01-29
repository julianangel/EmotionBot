/*
 * PlatformDescription.h
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#ifndef PLATFORMDESCRIPTION_H_
#define PLATFORMDESCRIPTION_H_

#include <string>
#include <map>

using std::map;
using std::string;

class PlatformDescription {
public:
	PlatformDescription();
	virtual ~PlatformDescription();
	map<string, string> getSimpleActionsAvailable();
	void setSimpleActionsAvailable(map<string, string> simple_actions_available);
	void addSimpleActionAvailable(string simple_action);
	void setPlatformName(string platform_name);
	string getPlatformName();
private:
	map<string, string> simple_actions_available;
	string platform_name;
};

#endif /* PLATFORMDESCRIPTION_H_ */
