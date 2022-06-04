#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H
#include "Transformation.h"
#include "Point.h"
#include <vector>

class Translate : public Transformation {

private:
    double x, y, z;
    double time;
    bool align;

public:

    Translate(double x,double y,double z);
    Translate(double time, bool align);
    Translate()=default;
    void transform() override;

    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    double getZ() const;
    void setZ(double z);
    double getTime() const;
    void setTime(double time);
    bool getAlign();
    void setAlign(bool align);
};


#endif
