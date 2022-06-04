#include <vector>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Group.h"
#include "Camera.h"
#include "Light.h"
#include <bits/stdc++.h>
#include "tinyxml2/tinyxml2.h"


using namespace tinyxml2;
using namespace std;

void renderScene(void);
void draw(Group gr);
void readXML(char *s);
void read3d(const char *s,Group *group_input);
void changeSize(int w, int h);
void processKeys(unsigned char c, int xx, int yy);
//void processSpecialKeys(int key, int xx, int yy);
Group readGroupXML(XMLElement *elem);
void readCameraXML(XMLElement *elem);
//void loadGroupsVBO(Group g);
