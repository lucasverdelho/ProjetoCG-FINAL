#include "Light.h"


Light::Light(const char *type, float x, float y, float z) {

    if(strcmp(type,"directional")==0){

        this->dir[0] = x;
        this->dir[1] = y;
        this->dir[2] = z;
        this->dir[3] = 0.0f;

    }
    else if(strcmp(type,"point")==0){

        this->pos[0] = x;
        this->pos[1] = y;
        this->pos[2] = z;
        this->pos[3] = 1.0f;

    }

    strcpy(this->type,type);

}


Light::Light(const char *type, float dirX, float dirY, float dirZ, float posX, float posY, float posZ, float cutoff) {

    strcpy(this->type,type);
    this->dir[0] = dirX;
    this->dir[1] = dirY;
    this->dir[2] = dirZ;
    this->pos[0] = posX;
    this->pos[1] = posY;
    this->pos[2] = posZ;
    this->pos[3] = 1.0f;
    this->cutoff = cutoff;

}

const char *Light::getType() const {
    return type;
}

float Light::getCutoff() const {
    return cutoff;
}

const float *Light::getDir() const {
    return dir;
}

const float *Light::getPos() const {
    return pos;
}
