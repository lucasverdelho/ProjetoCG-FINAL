#ifndef ENGINE_COLOUR_H
#define ENGINE_COLOUR_H
#include <tuple>

class Colour {

private:

    float diffuse[4];
    float ambient[4];
    float specular[4];
    float emissive[4];
    float shininess;


public:

    Colour(float diffuseR,float diffuseG ,float diffuseB, float ambientR,float ambientG ,float ambientB, float specularR,float specularG ,float specularB, float emissiveR,float emissiveG ,float emissiveB, float shininess);

    Colour()=default;

    const float *getDiffuse() const;

    const float *getAmbient() const;

    const float *getSpecular() const;

    const float *getEmissive() const;

    float getShininess() const;

};

#endif
