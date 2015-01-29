/*
 * PlatformTest1.h
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#ifndef PLATFORMTEST1_H_
#define PLATFORMTEST1_H_

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "../../general_description/platform_description/PlatformDescription.h"

using std::map;
using boost::shared_ptr;
using boost::make_shared;

class PlatformTest1 {
public:
	PlatformTest1();
	virtual ~PlatformTest1();
	map<string, shared_ptr<PlatformDescription> > getPlatformDescription();
private:
	map<string, shared_ptr<PlatformDescription> > platforms_description;
};

#endif /* PLATFORMTEST1_H_ */
