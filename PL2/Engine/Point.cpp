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

Point::Point(const Point &p) {
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
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


Point::Point(float x, float y, float z, float normalX, float normalY, float normalZ, float textX, float textY) {

    this->x = x;
    this->y = y;
    this->z = z;
    this->normalX = normalX;
    this->normalY = normalY;
    this->normalZ = normalZ;
    this->textX = textX;
    this->textY = textY;

}

float Point::getNormalX() const {
    return normalX;
}

float Point::getNormalY() const {
    return normalY;
}

float Point::getNormalZ() const {
    return normalZ;
}

float Point::getTextX() const {
    return textX;
}

float Point::getTextY() const {
    return textY;
}

Point::~Point() = default;




