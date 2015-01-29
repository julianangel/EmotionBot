///////////////////////////////////////////////////////////
//  Landmark.cpp
//  Implementation of the Class Landmark
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Landmark.h"


Landmark::Landmark(){
	this->id_landmakr = -1;
	this->observation = "";
	this->type_landmark = Unknown_Landmark;
}



Landmark::~Landmark(){

}

void Landmark::setQuaternionX(float x){
	pose.setX(x);
}
void Landmark::setQuaternionY(float y){
	pose.setY(y);
}
void Landmark::setQuaternionZ(float z){
	pose.setZ(z);
}
void Landmark::setQuaternionW(float w){
	pose.setW(w);
}
void Landmark::setQuaterion(float x, float y, float z, float w){
	pose.setQuaternion(x,y,z,w);
}

float Landmark::getQuaterionX(){
	return pose.getX();
}
float Landmark::getQuaterionY(){
	return pose.getY();
}
float Landmark::getQuaterionZ(){
	return pose.getZ();
}
float Landmark::getQuaterionW(){
	return pose.getW();
}


int Landmark::getIdLandmakr() {
	return this->id_landmakr;
}

void Landmark::setIdLandmakr(int idLandmakr) {
	this->id_landmakr = idLandmakr;
}

std::string Landmark::getObservation()  {
	return this->observation;
}

void Landmark::setObservation(const std::string observation) {
	this->observation = observation;
}

TypeLandmark Landmark::getTypeLandmark()  {
	return this->type_landmark;
}

void Landmark::setTypeLandmark(TypeLandmark typeLandmark) {
	this->type_landmark = typeLandmark;
}


