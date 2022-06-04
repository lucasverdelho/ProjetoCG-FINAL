#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H
#include "Solid.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"
#include <stdio.h>

class Group {

private:

    std::vector<char> instrucoes; //pode ser r(rotation), t(translate)
    std::vector<Solid> models;
    std::vector<Scale> scales;
    std::vector<Rotate> rotations;
    std::vector<Translate> translations;
    std::vector<Group> filhos;
    std::vector<Point> points;//para a translação
    float angle;
	
	
public:

    Group()=default;
    //Group(std::vector<char>, std::vector<Solid>, std::vector<Scale>, std::vector<Rotate>, std::vector<Translate>, std::vector<Group>);
    void addModels(Solid s);
    void addTranslation(Translate t);
    void addRotation(Rotate r);
    void addScale(Scale s);
    void addGroup(Group g);

    std::vector<char> getInstrucoes();

    std::vector<Solid> getModels();

    std::vector<Scale> getScales();

    std::vector<Rotate> getRotations();

    std::vector<Translate> getTranslations();

    void print();

    std::vector<Group> getFilhos();

    void loadGroup();

    void drawVBOs();

    void loadGroupsVBO();

    void addPoint(Point point);

    std::vector<Point> getPoints();

    void setAngle(float angle);

    float getAngle() const;

};


#endif
