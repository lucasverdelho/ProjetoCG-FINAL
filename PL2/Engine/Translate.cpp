#include "Translate.h"

Translate :: Translate(double x,double y,double z){

    this->x = x;
    this->y = y;
    this->z = z;
    this->time = -1;
    //Como este campo é uma unidade de tempo, ou seja, sempre >=0 este valor é
    //simbólico para poder identificar a diferença entre os 2 tipos de translações

}

Translate::Translate(double time, bool align) {

    this->time = time;
    this->align = align;

}

void Translate::transform(){

    glTranslatef(this->x,this->y,this->z);

}


double Translate::getX() const {
    return x;
}

void Translate::setX(double x) {
    Translate::x = x;
}

double Translate::getY() const {
    return y;
}

void Translate::setY(double y) {
    Translate::y = y;
}

double Translate::getZ() const {
    return z;
}

void Translate::setZ(double z) {
    Translate::z = z;
}

double Translate::getTime() const {
    return time;
}

void Translate::setTime(double time) {
    Translate::time = time;
}

bool Translate::getAlign() {
    return align;
}

void Translate::setAlign(bool align) {
    Translate::align = align;
}








