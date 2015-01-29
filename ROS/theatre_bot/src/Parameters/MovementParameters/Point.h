///////////////////////////////////////////////////////////
//  Point.h
//  Implementation of the Class Point
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(POINT_H_)
#define POINT_H_

#include "Position.h"
#include "Quaternion.h"

class Point : public Position
{

public:
	Point();
	virtual ~Point();

	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void setQuaternionX(float x);
	void setQuaternionY(float y);
	void setQuaternionZ(float z);
	void setQuaternionW(float w);
	void setQuaterion(float x, float y, float z, float w);

	float getQuaterionX();
	float getQuaterionY();
	float getQuaterionZ();
	float getQuaterionW();

protected:
	float x;
	float y;
	float z;
	Quaternion pose;
};
#endif // !defined(POINT_H_)