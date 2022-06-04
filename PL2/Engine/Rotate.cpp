#include "Rotate.h"


Rotate::Rotate(double angle_time, double x, double y, double z,int qual) {

    if(qual==1) {
        this->angle = angle_time;
        this->time = -1;
    }
    else{
        this->angle=0;
        this->time = angle_time;
    }
    this->x = x;
    this->y = y;
    this->z = z;


}


double Rotate::getTime() const {
    return time;
}

double Rotate::getAngle() const {
    return angle;
}

void Rotate::setAngle(double angle) {
    Rotate::angle = angle;
}

double Rotate::getX() const {
    return x;
}

void Rotate::setX(double x) {
    Rotate::x = x;
}

double Rotate::getY() const {
    return y;
}

void Rotate::setY(double y) {
    Rotate::y = y;
}

double Rotate::getZ() const {
    return z;
}

void Rotate::setZ(double z) {
    Rotate::z = z;
}

void Rotate::transform() {
    glRotatef(this->angle, this->x, this->y, this->z);
}

void Rotate::transform(double angle_in) {
    glRotatef(angle_in, this->x, this->y, this->z);
}

