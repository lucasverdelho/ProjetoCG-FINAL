#include "Triangle.h"

Triangle :: Triangle()=default;


Triangle :: Triangle(Point &p1, Point &p2, Point &p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Triangle :: Triangle(const Triangle &t) {
    this->p1 = t.p1;
    this->p2 = t.p2;
    this->p3 = t.p3;
}


void Triangle :: drawTriangle(){

    glVertex3f(this->p1.getX(),this->p1.getY(),this->p1.getZ());
    glVertex3f(this->p2.getX(),this->p2.getY(),this->p2.getZ());
    glVertex3f(this->p3.getX(),this->p3.getY(),this->p3.getZ());

}


void Triangle :: loadTriangleVBO(std :: vector<float> *points){

    points->push_back(this->p1.getX());
    points->push_back(this->p1.getY());
    points->push_back(this->p1.getZ());

    points->push_back(this->p2.getX());
    points->push_back(this->p2.getY());
    points->push_back(this->p2.getZ());

    points->push_back(this->p3.getX());
    points->push_back(this->p3.getY());
    points->push_back(this->p3.getZ());

}

void Triangle :: loadNormals(std::vector<float> *normals){

    normals->push_back(this->p1.getNormalX());
    normals->push_back(this->p1.getNormalY());
    normals->push_back(this->p1.getNormalZ());

    normals->push_back(this->p2.getNormalX());
    normals->push_back(this->p2.getNormalY());
    normals->push_back(this->p2.getNormalZ());

    normals->push_back(this->p3.getNormalX());
    normals->push_back(this->p3.getNormalY());
    normals->push_back(this->p3.getNormalZ());

}

void Triangle :: loadTextures(std::vector<float> *textures){

    textures->push_back(this->p1.getTextX());
    textures->push_back(this->p1.getTextY());

    textures->push_back(this->p2.getTextX());
    textures->push_back(this->p2.getTextY());

    textures->push_back(this->p3.getTextX());
    textures->push_back(this->p3.getTextY());

}

const Point &Triangle::getP1() const {
    return p1;
}

const Point &Triangle::getP2() const {
    return p2;
}

const Point &Triangle::getP3() const {
    return p3;
}

