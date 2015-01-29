/*
 * PlatformDescription.h
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#ifndef PLATFORMDESCRIPTION_H_
#define PLATFORMDESCRIPTION_H_

#include <string>
//#include <vector>
#include <map>
//#include <boost/shared_ptr.hpp>

using std::map;
using std::string;
//using std::vector;
//using boost::shared_ptr;
/*
 * TODO change the string to the new parameters
 * for this purpose it should be used the shared_ptr
 */
class PlatformDescription {
public:
	PlatformDescription();
	virtual ~PlatformDescription();
	map<string, string> getSimpleActionsAvailable();
	/*map<string, shared_ptr<PlatformActionDescription> > getSimpleActionsAvailable();
	void setSimpleActionsAvailable(
			map<string, shared_ptr<PlatformActionDescription> > simple_actions_available);
	void addSimpleActionAvailable(string simple_action, shared_ptr<PlatformActionDescription> parameter);*/
	void setSimpleActionsAvailable(map<string, string> simple_actions_available);
	void addSimpleActionAvailable(string simple_action);
	void setPlatformName(string platform_name);
	string getPlatformName();

private:
	/*map<string, shared_ptr<PlatformActionDescription>string >*/
	map <string,string> simple_actions_available;
	string platform_name;
};

#endif /* PLATFORMDESCRIPTION_H_ */
