#ifndef ENGINE_SCALE_H
#define ENGINE_SCALE_H
#include "Transformation.h"


class Scale : public Transformation{

private:
    double x;
    double y;
    double z;

public:

    void transform();

    Scale(double x,double y,double z);

    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    double getZ() const;
    void setZ(double z);
};


#endif
