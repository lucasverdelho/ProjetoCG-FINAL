#include <cstddef>
#include "Triangle.h"


Triangle :: Triangle()=default;

Triangle :: Triangle(Point p1, Point p2, Point p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Point Triangle :: getP1() {
	return this->p1;
}

Point Triangle :: getP2() {
	return this->p2;
}

Point Triangle :: getP3() {
	return this->p3;
}

void Triangle :: setP1(Point pp1) {
	this->p1 = pp1;
}

void Triangle :: setP2(Point pp2) {
	this->p2 = pp2;
}

void Triangle :: setP3(Point pp3) {
	this->p3 = pp3;
}

void Triangle :: drawTriangle(){

    glVertex3f(this->p1.getX(),this->p1.getY(),this->p1.getZ());
    glVertex3f(this->p2.getX(),this->p2.getY(),this->p2.getZ());
    glVertex3f(this->p3.getX(),this->p3.getY(),this->p3.getZ());


}

