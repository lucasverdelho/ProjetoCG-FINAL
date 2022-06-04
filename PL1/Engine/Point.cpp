#include "Point.h"


Point::Point() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
	this->y = y;
	this->z = z;
}


float Point :: getX() {
	return this->x;
}

float Point :: getY() {
	return this->y;
}

float Point :: getZ() {
	return this->z;
}

void Point :: setX(float x) {
	this->x = x;
}

void Point :: setY(float y) {
	this->y = y;
}

void Point :: setZ(float z) {
	this->z = z;
}




