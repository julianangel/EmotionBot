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
	platform_description->addSimpleActionAvailable("not_do_anything");
	platform_description->addSimpleActionAvailable("move_body");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("move_torso");
	platform_description->addSimpleActionAvailable("oscillate_body");
	platform_description->addSimpleActionAvailable("oscillate_shoulder");
	platform_description.reset(new PlatformDescription);
	platform_description->setPlatformName("triskar_small");
	platform_description->addSimpleActionAvailable("not_do_anything");
	platform_description->addSimpleActionAvailable("move_body");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("move_torso");
	platform_description->addSimpleActionAvailable("oscillate_body");
	platform_description->addSimpleActionAvailable("oscillate_shoulder");
	//this->platforms_description.push_back(platform_description);
	this->platforms_description[platform_description->getPlatformName()] = platform_description;
	platform_description.reset(new PlatformDescription);
	platform_description->setPlatformName("nao");
	platform_description->addSimpleActionAvailable("not_do_anything");
	platform_description->addSimpleActionAvailable("move_body");
	platform_description->addSimpleActionAvailable("move_shoulder");
	platform_description->addSimpleActionAvailable("oscillate_body");
	platform_description->addSimpleActionAvailable("oscillate_shoulder");
	platform_description->addSimpleActionAvailable("move_torso");
	platform_description->addSimpleActionAvailable("speak");
	//this->platforms_description.push_back(platform_description);
	this->platforms_description[platform_description->getPlatformName()] = platform_description;
}

PlatformTest1::~PlatformTest1() {

}

map<string, shared_ptr<PlatformDescription> > PlatformTest1::getPlatformDescription(){
	return this->platforms_description;
}


map<string, string> PlatformTest1::getPlatformAction(string desire_platform){
	return this->platforms_description[desire_platform]->getSimpleActionsAvailable();
}
