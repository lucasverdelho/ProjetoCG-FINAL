#include "main.h"
#include <vector>

Group group = Group();
Camera c;
vector<Light> globalLights;
float alfa = 0.0f, Beta = 0.0f, raio = 10.0f;
int livre = 0;
int axis = 0;
int lines = 1;
int luz = 1;

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(c.getFov(), ratio, c.getNear(), c.getFar());
	glMatrixMode(GL_MODELVIEW);
}


void read3d(const char *s,Group *group_input,Solid solid){

    ifstream f;
    f.open(s);

    float x,y,z,normalX,normalY,normalZ,textX,textY;
    char sep,reflections;
    int pontos,i=1;

    if (!f) {
        cout << "Unable to open file";
        exit(1);
    }

    //ler o número de pontos
    f >> pontos;
    f >> sep;
    f >> reflections;

    Point p1,p2,p3;
    while(i<=pontos){

        f >> x;
        f >> sep;
        f >> y;
        f >> sep;
        f >> z;

        if(reflections=='l') {
            f >> sep;
            f >> normalX;
            f >> sep;
            f >> normalY;
            f >> sep;
            f >> normalZ;
            f >> sep;
            f >> textX;
            f >> sep;
            f >> textY;
        }

        switch (i%3) {

            case 0: {
                if(reflections=='l')
                    p3 = Point(x, y, z, normalX, normalY, normalZ, textX, textY);
                else
                    p3 = Point(x, y, z);
                Triangle triangulo = Triangle(p1, p2, p3);
                solid.addTriangle(triangulo);

                break;
            }

            case 1: {
                if(reflections=='l')
                    p1 = Point(x, y, z, normalX, normalY, normalZ, textX, textY);
                else
                    p1 = Point(x, y, z);
                break;
            }

            case 2: {
                if(reflections=='l')
                    p2 = Point(x, y, z, normalX, normalY, normalZ, textX, textY);
                else
                    p2 = Point(x, y, z);
                break;
            }

        }

        i++;
    }

    group_input->addModels(solid);
    f.close();

}


void readTransformation(XMLElement *transformation,Group *group_input){

    double angle,x,y,z,time;
    bool align;

    for(XMLElement *tr=transformation->FirstChildElement(); tr; tr=tr->NextSiblingElement()){

        if (strcmp(tr->Name(), "scale") == 0) {

            tr->QueryDoubleAttribute("x", &x);
            tr->QueryDoubleAttribute("y", &y);
            tr->QueryDoubleAttribute("z", &z);

            Scale s = Scale(x, y, z);
            group_input->addScale(s);

        } else if (strcmp(tr->Name(), "translate") == 0) {


            //Fases anteriores
            if(tr->FindAttribute("x")) {
                tr->QueryDoubleAttribute("x", &x);
                tr->QueryDoubleAttribute("y", &y);
                tr->QueryDoubleAttribute("z", &z);

                Translate t = Translate(x, y, z);

                group_input->addTranslation(t);
            }

            //Fase 3
            else if(tr->FindAttribute("time")) {

                tr->QueryDoubleAttribute("time", &time);
                tr->QueryBoolAttribute("align", &align);

                Translate t = Translate(time, align);
                group_input->addTranslation(t);

                XMLElement *point = tr->FirstChildElement("point");

                while(point != nullptr){

                    point->QueryDoubleAttribute("x", &x);
                    point->QueryDoubleAttribute("y", &y);
                    point->QueryDoubleAttribute("z", &z);

                    Point p = Point((float) x,(float) y,(float) z);
                    group_input->addPoint(p);

                    point = point->NextSiblingElement();

                }

            }

        } else if (strcmp(tr->Name(), "rotate") == 0) {


            tr->QueryDoubleAttribute("x", &x);
            tr->QueryDoubleAttribute("y", &y);
            tr->QueryDoubleAttribute("z", &z);

            if(tr->FindAttribute("time")){

                tr->QueryDoubleAttribute("time", &time);
                Rotate r = Rotate(time,x, y, z,0);
                group_input->addRotation(r);

            }
            else {
                tr->QueryDoubleAttribute("angle", &angle);
                Rotate r = Rotate(angle, x, y, z,1);
                group_input->addRotation(r);
            }


        }

    }

}


void readModels(XMLElement *models,Group *group_input){

    for(XMLElement *model = models->FirstChildElement("model");model;model = model->NextSiblingElement()) {

        Solid solid = Solid();
        float shininess;
        float rgb[4][3];
        const char *file;
        const char *textureFile;
        model->QueryStringAttribute("file",&file);
        char p[128] = "../../Models/";
        char textureP[128] = "../../Texturas/";
        char *texturePath;
        char *pathM = strcat(p, (char *) file);

        XMLElement *colour = model->FirstChildElement("color");
        if(colour){

            XMLElement *RGBs = colour->FirstChildElement();
            for(int i=0;i<4;i++,RGBs=RGBs->NextSiblingElement()){

                RGBs->QueryFloatAttribute("R",&rgb[i][0]);
                RGBs->QueryFloatAttribute("G",&rgb[i][1]);
                RGBs->QueryFloatAttribute("B",&rgb[i][2]);

                rgb[i][0]/=255.0f;
                rgb[i][1]/=255.0f;
                rgb[i][2]/=255.0f;

            }

            RGBs->QueryFloatAttribute("value",&shininess);


            Colour colourModel = Colour(rgb[0][0],rgb[0][1],rgb[0][2],rgb[1][0],
                                rgb[1][1],rgb[1][2],rgb[2][0],rgb[2][1],
                                rgb[2][2],rgb[3][0],rgb[3][1],rgb[3][2],shininess);
            solid.addColour(colourModel);

        }
        //Default color
        else{
            Colour colourModelDefault = Colour(200.0f/255.0f,200.0f/255.0f,200.0f/255.0f,
                                        50.0f/255.0f,50.0f/255.0f,50.0f/255.0f,0.0f,
                                        0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
            solid.addColour(colourModelDefault);
        }


        XMLElement *texture = model->FirstChildElement("texture");
        if(texture){

            texture->QueryStringAttribute("file",&textureFile);
            texturePath = strcat(textureP,textureFile);
            solid.addTexture(texturePath);

        }

        read3d(pathM,group_input,solid);

    }

}


Group readGroupXML(XMLElement *elem){


    Group g = Group();

    XMLElement *transform = elem->FirstChildElement("transform");
    if(transform)
        readTransformation(transform,&g);

    XMLElement *models = elem->FirstChildElement("models");
    if(models)
        readModels(models,&g);

    for(XMLElement *filho = elem->FirstChildElement("group");filho;filho=filho->NextSiblingElement()){

        Group grupoFilho = readGroupXML(filho);
        g.addGroup(grupoFilho);

    }

    return g;

}


void readCameraXML(XMLElement *elem){

    XMLElement *camera = elem->FirstChildElement("camera");

    double d1,d2,d3;

    //Camera
    XMLElement *position = camera->FirstChildElement("position");


    position->QueryDoubleAttribute("x", &d1);
    position->QueryDoubleAttribute("y", &d2);
    position->QueryDoubleAttribute("z", &d3);

    c.setPosX(d1);
    c.setPosY(d2);
    c.setPosZ(d3);

    XMLElement *lookAt = camera->FirstChildElement("lookAt");
    lookAt->QueryDoubleAttribute("x", &d1);
    lookAt->QueryDoubleAttribute("y", &d2);
    lookAt->QueryDoubleAttribute("z", &d3);

    c.setLookAtX(d1);
    c.setLookAtY(d2);
    c.setLookAtZ(d3);

    XMLElement *up = camera->FirstChildElement("up");
    up->QueryDoubleAttribute("x", &d1);
    up->QueryDoubleAttribute("y", &d2);
    up->QueryDoubleAttribute("z", &d3);

    c.setUpX(d1);
    c.setUpY(d2);
    c.setUpZ(d3);

    XMLElement *projection = camera->FirstChildElement("projection");
    projection->QueryDoubleAttribute("fov", &d1);
    projection->QueryDoubleAttribute("near", &d2);
    projection->QueryDoubleAttribute("far", &d3);

    c.setFov(d1);
    c.setNear(d2);
    c.setFar(d3);

}


int getLightI(int i){
    int x;
    switch (i) {
        case 0:
            x = GL_LIGHT0;
            break;
        case 1:
            x = GL_LIGHT1;
            break;
        case 2:
            x = GL_LIGHT2;
            break;
        case 3:
            x = GL_LIGHT3;
            break;
        case 4:
            x = GL_LIGHT4;
            break;
        case 5:
            x = GL_LIGHT5;
            break;
        case 6:
            x = GL_LIGHT6;
            break;
        case 7:
            x = GL_LIGHT7;
            break;
        default:
            printf("Too many lights\n");
            exit(1);
    }
    return x;
}


void readLights(XMLElement *elem){//falta atribuir os valores, criar classes...

    const char *type;
    float posX,posY,posZ,dirX,dirY,dirZ,cutoff;
    int i=0;

    for(XMLElement *l=elem->FirstChildElement(); l; l=l->NextSiblingElement()){


        l->QueryStringAttribute("type",&type);
        l->QueryFloatAttribute("posx",&posX);
        l->QueryFloatAttribute("posy",&posY);
        l->QueryFloatAttribute("posz",&posZ);
        l->QueryFloatAttribute("dirx",&dirX);
        l->QueryFloatAttribute("diry",&dirY);
        l->QueryFloatAttribute("dirz",&dirZ);
        l->QueryFloatAttribute("cutoff",&cutoff);

        if(strcmp("directional",type)==0)
            globalLights.push_back(Light(type, dirX, dirY, dirZ));
        else if(strcmp("point",type)==0)
            globalLights.push_back(Light(type, posX, posY, posZ));
        else if(strcmp("spot",type)==0)
            globalLights.push_back(Light(type, dirX, dirY, dirZ, posX, posY, posZ, cutoff));

        i++;

    }

}


void readXML(char *s){

    XMLDocument xml;

    xml.LoadFile(s);

    XMLElement *root = xml.RootElement();
    if(root) {

        //Camera
        readCameraXML(root);

        //Lights
        XMLElement *lights = root->FirstChildElement("lights");
        if(lights) {

            glEnable(GL_LIGHTING);
            readLights(lights);

        }

        //Group
        XMLElement *grupo = root->FirstChildElement("group");
        group = readGroupXML(grupo);

    }

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

    //A posição inicial apresentada inicialmente a do xml,
    //depois com a interação com o teclado, a câmara torna-se "livre"
    GLfloat x = livre ? raio * cos(Beta) * sin(alfa) : c.getPosX();
    GLfloat y = livre ? raio * sin(Beta) : c.getPosY();
    GLfloat z = livre ? raio * cos(Beta) * cos(alfa) : c.getPosZ();


	gluLookAt(x,y,z,
		c.getLookAtX(), c.getLookAtY(), c.getLookAtZ(),
		c.getUpX(),c.getUpY(), c.getUpZ());


    if(axis){
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);

        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();
        glEnable(GL_LIGHTING);
    }

    glColor3f(1.0f,1.0f,1.0f);


    //Lights
    if(luz) {
        glEnable(GL_LIGHTING);
        for (int i = 0; i < globalLights.size(); i++) {

            int GL_LightI = getLightI(i);

            if (strcmp("point", globalLights[i].getType()) == 0) {

                glLightfv(GL_LightI, GL_POSITION, globalLights[i].getPos());

            } else if (strcmp("directional", globalLights[i].getType()) == 0) {

                glLightfv(GL_LightI, GL_POSITION, globalLights[i].getDir());

            } else if (strcmp("spot", globalLights[i].getType()) == 0) {

                const float cutoff = (const float) globalLights[i].getCutoff();
                float dir[3];
                dir[0] = globalLights[i].getDir()[0];
                dir[1] = globalLights[i].getDir()[1];
                dir[2] = globalLights[i].getDir()[2];

                glLightfv(GL_LightI, GL_POSITION, globalLights[i].getPos());
                glLightfv(GL_LightI, GL_SPOT_DIRECTION, dir);
                glLightfv(GL_LightI, GL_SPOT_CUTOFF, &cutoff);

            }

        }
    }
    else{
        glDisable(GL_LIGHTING);
    }

    //desenhar aqui
    glPolygonMode(GL_FRONT, lines ? GL_FILL : GL_LINE);

    draw(group);

	// End of frame
    glutSwapBuffers();

}

//---------------------------- CATMULL-ROM ---------------------------------

float prev_y[3] = { 0,-1,0 };

std::vector<Point> points;

int POINT_COUNT = 1;

float t_global = 0;


void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float *a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}


float length(float *v) {

    float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return res;

}


void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}


void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float* pos, float* deriv) {

    // catmull-rom matrix
    float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f} };


    float tt[4] = { t * t * t, t * t, t, 1 };

    float td[4] = { 3 * t * t, 2 * t, 1, 0 };

    float aux[4];

    float pp[4] = { p0.getX(), p1.getX(), p2.getX(), p3.getX() };
    multMatrixVector((float*)m, pp, aux);
    pos[0] = tt[0] * aux[0] + tt[1] * aux[1] + tt[2] * aux[2] + tt[3] * aux[3];
    deriv[0] = td[0] * aux[0] + td[1] * aux[1] + td[2] * aux[2] + td[3] * aux[3];

    float pp1[4] = { p0.getY(), p1.getY(), p2.getY(), p3.getY() };
    multMatrixVector((float*)m, pp1, aux);
    pos[1] = tt[0] * aux[0] + tt[1] * aux[1] + tt[2] * aux[2] + tt[3] * aux[3];
    deriv[1] = td[0] * aux[0] + td[1] * aux[1] + td[2] * aux[2] + td[3] * aux[3];

    float pp2[4] = { p0.getZ(), p1.getZ(), p2.getZ(), p3.getZ() };
    multMatrixVector((float*)m, pp2, aux);
    pos[2] = tt[0] * aux[0] + tt[1] * aux[1] + tt[2] * aux[2] + tt[3] * aux[3];
    deriv[2] = td[0] * aux[0] + td[1] * aux[1] + td[2] * aux[2] + td[3] * aux[3];

}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv) {

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    getCatmullRomPoint(t, points.at(indices[0]), points.at(indices[1]), points.at(indices[2]), points.at(indices[3]), pos, deriv);
}

void renderCatmullRomCurve() {

    // desenhar os segmentos de linha "ligados"
    float pos[3];
    float deriv[3];

    glBegin(GL_LINE_LOOP);

    for(int gt=0;gt<100;gt++){
        getGlobalCatmullRomPoint(gt/100.0f, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
    }

    glEnd();


    //desenhar as linhas da derivada
    glBegin(GL_LINE);

    for(int gt=0;gt<100;gt++){

        getGlobalCatmullRomPoint(gt/100.0f, pos, deriv);
        glVertex3f(deriv[0], deriv[1], deriv[2]);

    }

    glEnd();

}

void renderCatmull(float time,bool align) {

    float pos[3], deriv[3], m[16],z[3],y[3],x[3];

    glPushMatrix();

    //renderCatmullRomCurve();

    t_global = ((float) glutGet(GLUT_ELAPSED_TIME) / 1000) / ((float)time);
    getGlobalCatmullRomPoint(t_global, pos, deriv);

    glTranslatef(pos[0], pos[1], pos[2]);

    if(align){
        for (int i = 0; i < 3; i++) x[i] = deriv[i];
        normalize(x);
        cross(x, prev_y, z);
        normalize(z);
        cross(z, x, y);
        normalize(y);
        memcpy(prev_y, y, 3 * sizeof(float));

        buildRotMatrix(x, y, z, m);

        glMultMatrixf(m);
    }

}


void draw(Group gr){

    glPushMatrix();

    int r=0,t=0;
    double time;
    for(char tr:gr.getInstrucoes()){

        Rotate rotate;
        Translate translate;

        switch (tr) {

            case 'r':

                rotate = gr.getRotations()[r];
                time = rotate.getTime();
                //Aqui é um rotate normal
                if(time==-1) {
                    rotate.transform();
                }
                else{

                    gr.setAngle(((float)glutGet(GLUT_ELAPSED_TIME) * 360 / 1000) / ((float)time));
                    rotate.transform(gr.getAngle());

                }

                r++;
                break;

            case 't':

                translate = gr.getTranslations()[t];

                //Aqui é uma translação normal
                if(translate.getTime()==-1) {
                    translate.transform();
                }
                else{

                    points=gr.getPoints();
                    POINT_COUNT = points.size();
                    renderCatmull((float) translate.getTime(),translate.getAlign());

                }

                t++;
                break;
        }

    }

    for(Scale s:gr.getScales()){
        s.transform();
    }

    gr.drawVBOs();

    for (Group g: gr.getFilhos()) {
        draw(g);
    }

    glPopMatrix();

}


void processKeys(unsigned char key, int xx, int yy) {

    // put code to process regular keys in here
    switch (key) {
        case 'a':
            alfa += 10.0 * M_PI/180;
            livre = 1;
            break;
        case 'd':
            alfa -= 10.0 * M_PI / 180;
            livre = 1;
            break;
        case 's':
            Beta += 10.0 * M_PI / 180;
            if (fabsf(Beta) > 1.5) Beta = 1.5;
            livre = 1;
            break;
        case 'w':
            Beta -= 10.0 * M_PI / 180;
            if (fabsf(Beta) > 1.5) Beta = -1.5;
            livre = 1;
            break;
        case '+':
            livre = 1;
            raio = max(raio-1,2.0f);
            break;
        case '-':
            livre = 1;
            raio = min(raio+1,120.0f);
            break;
        case 'r':
            livre=0;
            raio=5;
            break;
        case 'q':
            axis = !axis;
            break;
        case 'l':
            lines = !lines;
        case 'e':
            luz = !luz;
            break;

    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG-Project");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);

    //Glew init
    glewInit();

    //  OpenGL settings
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glEnable(GL_RESCALE_NORMAL);

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    readXML(argv[1]);
    group.loadGroupsVBO();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);

    for(int i=0;i<globalLights.size();i++) {
        int glLight = getLightI(i);
        glEnable(glLight);
    }

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    //float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);


    //group.print();

    // enter GLUT's main cycle
    glutMainLoop();

    return 0;
}
