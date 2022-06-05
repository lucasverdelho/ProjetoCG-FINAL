#include "Solid.h"


void Solid::addTexture(char *texturePath){
    strcpy(this->texturePath,texturePath);
}


void Solid::addTriangle(Triangle &t) {

    Triangle triangle = Triangle(t);
    this->s.push_back(triangle);

}


void Solid::addColour(Colour colour){
    this->colour = colour;
}


void Solid :: drawSolid(){

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(Triangle t:this->s){
        t.drawTriangle();
    }

    glEnd();

}


void Solid :: loadTexture(){

    unsigned int t, tw, th;
    unsigned char *textureData;

    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)this->texturePath);

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    textureData = ilGetData();

    glGenTextures(1, &this->idTextureData);
    glBindTexture(GL_TEXTURE_2D, this->idTextureData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);

}


void Solid :: loadSolidVBO(){

    std::vector<float> points;
    std::vector<float> normals;
    std::vector<float> textures;

    for(Triangle t : this->s){
        t.loadTriangleVBO(&points);
        t.loadNormals(&normals);
        t.loadTextures(&textures);
    }

    //Load dos Modelos
    this->vertexCount = points.size()/3;
    glGenBuffers(1,&this->idVBO);
    glBindBuffer(GL_ARRAY_BUFFER,this->idVBO);
    glBufferData(GL_ARRAY_BUFFER,points.size()*sizeof(float),points.data(),GL_STATIC_DRAW);

    //Load das normais
    glGenBuffers(1, &this->idNormals);
    glBindBuffer(GL_ARRAY_BUFFER, this->idNormals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);


    //Load das texturas
    glGenBuffers(1,&this->idTextures);
    glBindBuffer(GL_ARRAY_BUFFER,this->idTextures);
    glBufferData(GL_ARRAY_BUFFER,textures.size()*sizeof(float),textures.data(),GL_STATIC_DRAW);

}

void Solid :: drawSolidVBO(){

    glMaterialfv(GL_FRONT, GL_AMBIENT,this->getColour().getAmbient());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,this->getColour().getDiffuse());
    glMaterialfv(GL_FRONT, GL_EMISSION,this->getColour().getEmissive());
    glMaterialfv(GL_FRONT, GL_SPECULAR,this->getColour().getSpecular());
    glMaterialf(GL_FRONT, GL_SHININESS,this->getColour().getShininess());

    glBindTexture(GL_TEXTURE_2D,this->idTextureData);

    glBindBuffer(GL_ARRAY_BUFFER,this->idVBO);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER, this->idNormals);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->idTextures);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES,0,this->vertexCount);

    glBindTexture(GL_TEXTURE_2D,0);

}

const Colour &Solid::getColour() const {
    return colour;
}
