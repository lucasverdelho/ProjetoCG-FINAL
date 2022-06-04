#ifndef Triangle_h
#define Triangle_h
#include <iostream>
#include <vector>
#include "Point.h"
#include <GL/glut.h>

class Triangle {

private:
    Point p1;
    Point p2;
    Point p3;

public:

    Triangle();

    Triangle(const Triangle &t);

    Triangle(Point &p1, Point &p2, Point &p3);

    Triangle(const Point &p1, const Point &p2, const Point &p3);

    void drawTriangle();

    void loadTriangleVBO(std::vector<float> *points);

    void loadNormals(std::vector<float> *normals);

    void loadTextures(std::vector<float> *textures);

    const Point &getP1() const;

    const Point &getP2() const;

    const Point &getP3() const;

};

#endif