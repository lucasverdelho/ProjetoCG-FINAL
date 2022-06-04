#include "Group.h"

void Group :: addModels(Solid s) {

    this->models.push_back(s);

}

float Group::getAngle() const {
    return angle;
}

void Group::setAngle(float angle) {
    Group::angle = angle;
}

void Group :: addTranslation(Translate t) {

    this->translations.push_back(t);
    this->instrucoes.push_back('t');

}

void Group::addRotation(Rotate r){

    this->rotations.push_back(r);
    this->instrucoes.push_back('r');

}
void Group::addScale(Scale s){

    this->scales.push_back(s);

}


void Group ::addGroup(Group g) {

    this->filhos.push_back(g);

}


void Group::print(){

    printf("\nmodels:%zu   scales:%zu   rotations:%zu    translations:%zu     filhos:%zu\n",models.size(),scales.size(),rotations.size(),translations.size(),filhos.size());
    for(Group g:filhos)
        g.print();

}


std::vector<char> Group::getInstrucoes() {
    return instrucoes;
}

std::vector<Point> Group::getPoints(){
    return points;
}

std::vector<Solid> Group::getModels() {
    return models;
}

std::vector<Scale> Group::getScales() {
    return scales;
}

std::vector<Rotate> Group::getRotations() {
    return rotations;
}

std::vector<Translate> Group::getTranslations() {
    return translations;
}

std::vector<Group> Group::getFilhos() {
    return filhos;
}

void Group::loadGroup(){

    for(Solid &s:this->models){
        s.loadSolidVBO();
        s.loadTexture();//bruh???
    }

}


void Group::drawVBOs(){

    for(Solid s:this->models){

		s.drawSolidVBO();

    }

}


void Group::loadGroupsVBO(){

    this->loadGroup();

    for(Group &filho:this->filhos){

        filho.loadGroupsVBO();

    }

}

void Group::addPoint(Point p) {
    this->points.push_back(p);
}
