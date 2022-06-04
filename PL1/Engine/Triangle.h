#ifndef Triangle_h
#define Triangle_h
#include "Point.h"
#include <GL/glut.h>

class Triangle {

private:
    Point p1;
    Point p2;
    Point p3;

public:

    Triangle();

	Triangle(Point p1, Point p2, Point p3);

	Point getP1();

	Point getP2();

	Point getP3();

	void setP1(Point p1);

	void setP2(Point p2);

	void setP3(Point p3);

    void drawTriangle();

};

#endif 