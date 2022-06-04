#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H
#include "string.h"

class Light {

private:

    char type[16];
    float dir[4];
    float pos[4];
    float cutoff;

public:

    //Neste construtor pode ser directional ou point
    Light(const char *type,float x,float y,float z);

    //Spot
    Light(const char *type,float dirX,float dirY,float dirZ,float posX,float posY,float posZ,float cutoff);

    Light()=default;

    const char *getType() const;

    float getCutoff() const;

    const float *getDir() const;

    const float *getPos() const;

};


#endif
