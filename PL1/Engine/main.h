#include <GL/glut.h>
#include "tinyxml2/tinyxml2.h"
#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>
#include <math.h>
#define _USE_MATH_DEFINES
#include "Triangle.h"
#include "Point.h"
#include "tinyxml2/tinyxml2.h"


using namespace tinyxml2;
using namespace std;

void renderScene(void);
void draw();
void readXML(char *s);
void read3d(const char *s);
void changeSize(int w, int h);
void processKeys(unsigned char c, int xx, int yy);
void processSpecialKeys(int key, int xx, int yy);
