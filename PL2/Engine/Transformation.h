#ifndef ENGINE_TRANSFORMATION_H
#define ENGINE_TRANSFORMATION_H
#include <typeinfo>
#include <GL/glut.h>

class Transformation {

public:
    virtual void transform() = 0;

};

#endif