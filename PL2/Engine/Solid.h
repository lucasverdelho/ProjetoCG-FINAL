#ifndef ENGINE_SOLID_H
#define ENGINE_SOLID_H
#include <GL/glew.h>
#include <IL/il.h>
#include "Triangle.h"
#include "Colour.h"
#include "string.h"


class Solid {

private:
    std::vector<Triangle> s;
    GLuint idVBO;
    GLuint idNormals;
    GLuint idTextures;
    GLuint idTextureData = 0;
    int vertexCount;
    Colour colour;
    char texturePath[128];


public:

    Solid()=default;

    void addColour(Colour colour);

    void addTriangle(Triangle &t);

    void addTexture(char *texturePath);

    void drawSolid();

    void loadSolidVBO();

    void drawSolidVBO();

    const Colour &getColour() const;

    void loadTexture();

};


#endif
