#include "Colour.h"

Colour ::Colour(float diffuseR, float diffuseG, float diffuseB, float ambientR, float ambientG, float ambientB,
                float specularR, float specularG, float specularB, float emissiveR, float emissiveG, float emissiveB,
                float shininess){

    this->diffuse[0] = diffuseR;
    this->diffuse[1] = diffuseG;
    this->diffuse[2] = diffuseB;
    this->diffuse[3] = 1.0f;

    this->ambient[0] = ambientR;
    this->ambient[1] = ambientG;
    this->ambient[2] = ambientB;
    this->ambient[3] = 1.0f;

    this->specular[0] = specularR;
    this->specular[1] = specularG;
    this->specular[2] = specularB;
    this->specular[3] = 1.0f;

    this->emissive[0] = emissiveR;
    this->emissive[1] = emissiveG;
    this->emissive[2] = emissiveB;
    this->emissive[3] = 1.0f;

    this->shininess = shininess;

}


float Colour::getShininess() const {
    return shininess;
}

const float *Colour::getDiffuse() const {
    return diffuse;
}

const float *Colour::getAmbient() const {
    return ambient;
}

const float *Colour::getSpecular() const {
    return specular;
}

const float *Colour::getEmissive() const {
    return emissive;
}
