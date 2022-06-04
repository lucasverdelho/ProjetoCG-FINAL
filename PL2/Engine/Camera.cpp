#include "Camera.h"

double Camera :: getPosX(){
    return posX;
}

double Camera :: getPosY(){
    return posY;
}

double Camera :: getPosZ(){
    return posZ;
}

double Camera :: getLookAtX(){
    return lookAtX;
}

double Camera :: getLookAtY(){
    return lookAtY;
}

double Camera :: getLookAtZ(){
    return lookAtZ;
}

double Camera :: getUpX(){
    return upX;
}

double Camera :: getUpY(){
    return upY;
}

double Camera :: getUpZ(){
    return upZ;
}

double Camera :: getFov(){
    return fov;
}

double Camera :: getNear(){
    return near;
}

double Camera :: getFar(){
    return far;
}

void Camera :: setPosX(double posX) {
    Camera::posX = posX;
}

void Camera :: setPosY(double posY) {
    Camera::posY = posY;
}

void Camera :: setPosZ(double posZ) {
    Camera::posZ = posZ;
}

void Camera :: setLookAtX(double lookAtX) {
    Camera::lookAtX = lookAtX;
}

void Camera :: setLookAtY(double lookAtY) {
    Camera::lookAtY = lookAtY;
}

void Camera :: setLookAtZ(double lookAtZ) {
    Camera::lookAtZ = lookAtZ;
}

void Camera :: setUpX(double upX) {
    Camera::upX = upX;
}

void Camera :: setUpY(double upY) {
    Camera::upY = upY;
}

void Camera :: setUpZ(double upZ) {
    Camera::upZ = upZ;
}

void Camera :: setFov(double fov) {
    Camera::fov = fov;
}

void Camera :: setNear(double near) {
    Camera::near = near;
}

void Camera :: setFar(double far) {
    Camera::far = far;
}
