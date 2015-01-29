/*
 * PlatformTest1.cpp
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#include "PlatformTest1.h"

PlatformTest1::PlatformTest1() {
	shared_ptr<PlatformDescription> platform_description(new PlatformDescription);
	platform_description->setPlatformName("triskar_big");
	//this->platforms_description.push_back(platform_description);
	this->platforms_description[platform_description->getPlatformName()] = platform_description;
	platform_description->addSimpleActionAvailable("walk");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("oscillation_move");
	platform_description->addSimpleActionAvailable("oscillation_shoulder");
	platform_description.reset(new PlatformDescription);
	platform_description->setPlatformName("triskar_small");
	platform_description->addSimpleActionAvailable("walk");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("oscillation_move");
	platform_description->addSimpleActionAvailable("oscillation_shoulder");
	//this->platforms_description.push_back(platform_description);
	this->platforms_description[platform_description->getPlatformName()] = platform_description;
	platform_description.reset(new PlatformDescription);
	platform_description->setPlatformName("nao");
	platform_description->addSimpleActionAvailable("walk");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("oscillation_move");
	platform_description->addSimpleActionAvailable("oscillation_shoulder");
	platform_description->addSimpleActionAvailable("speak");
	//this->platforms_description.push_back(platform_description);
	this->platforms_description[platform_description->getPlatformName()] = platform_description;
}

PlatformTest1::~PlatformTest1() {

}

map<string, shared_ptr<PlatformDescription> > PlatformTest1::getPlatformDescription(){
	return this->platforms_description;
}
