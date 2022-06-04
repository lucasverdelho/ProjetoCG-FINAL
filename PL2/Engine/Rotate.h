#ifndef ENGINE_ROTATE_H
#define ENGINE_ROTATE_H
#include "Transformation.h"


class Rotate : public Transformation {

private:
    double angle,x,y,z,time;


public:

    Rotate()=default;
    Rotate(double angle_time,double x,double y,double z,int qual);
    void transform();
    double getAngle() const;
    void setAngle(double angle);
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    double getZ() const;
    void setZ(double z);
    double getTime() const;
    void transform(double angle_in);

};

#endif
