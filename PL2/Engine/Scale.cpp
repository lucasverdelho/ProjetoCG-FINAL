#include "Scale.h"

Scale::Scale(double x,double y,double z){

    this->x = x;
    this->y = y;
    this->z = z;


}

void Scale::transform() {

    glScalef(this->x,this->y,this->z);

}

void Scale::setX(double x) {
    Scale::x = x;
}

double Scale::getY() const {
    return y;
}

void Scale::setY(double y) {
    Scale::y = y;
}

double Scale::getZ() const {
    return z;
}

void Scale::setZ(double z) {
    Scale::z = z;
}
