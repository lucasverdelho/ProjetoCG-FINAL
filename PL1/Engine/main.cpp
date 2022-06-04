#include "main.h"

class camera{

public:
    double posX,posY,posZ;
    double lookAtX,lookAtY,lookAtZ;
    double upX,upY,upZ;
    double fov,near,far;

public:
    camera(){
        posX=0,posY=0,posZ=0;
        lookAtX=0,lookAtY=0,lookAtZ=0;
        upX=0,upY=0,upZ=0;
        fov=0,near=0,far=0;
    }

    void toString(){
        cout << "posX: " << posX << endl;
        cout << "posY: " << posY << endl;
        cout << "posZ: " << posZ << endl;
        cout << "lookAtX: " << lookAtX << endl;
        cout << "lookAtY: " << lookAtY << endl;
        cout << "lookAtZ: " << lookAtZ << endl;
        cout << "upX: " << upX << endl;
        cout << "upY: " << upY << endl;
        cout << "upZ: " << upZ << endl;
        cout << "fov: " << fov << endl;
        cout << "near: " << near << endl;
        cout << "far: " << far << endl;

    }

};


vector<Triangle> triangulos;
camera c;
float alfa = 0.0f, Beta = 0.0f, raio = 5.0f;
int livre = 0;

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(c.fov, ratio, c.near, c.far+100);
	glMatrixMode(GL_MODELVIEW);
}




void read3d(const char *s){

    ifstream f;

    //f.open("../../Models/box.3d");
    f.open(s);

    //string linha;
    float x,y,z;
    char sep;
    int pontos,i=1;

    if (!f) {
        cout << "Unable to open file";
        exit(1);
    }

    //ler o número de pontos
    f >> pontos;

    Triangle triangulo;
    tuple<Point,Point,Point> t;
    Point p1,p2,p3;

    while(i<=pontos){

        f >> x;
        f >> sep;
        f >> y;
        f >> sep;
        f >> z;

        switch (i%3) {

            case 0: {
                p3 = Point(x, y, z);
                triangulo = Triangle(p1, p2, p3);
                triangulos.push_back(triangulo);
                break;
            }

            case 1: {
                p1 = Point(x, y, z);
                break;
            }

            case 2: {
                p2 = Point(x, y, z);
                break;
            }

        }

        i++;
    }

    f.close();

}



void readXML(char *s){

    XMLDocument xml;

    const char *pathX = "../../test_files_phase_1/test_1_4.xml";

    xml.LoadFile(s);

    XMLElement *root = xml.RootElement();
    if(root != NULL) {
        XMLElement *camera = root->FirstChildElement("camera");

        //camera

        XMLElement *position = camera->FirstChildElement("position");
        position->QueryDoubleAttribute("x", &c.posX);
        position->QueryDoubleAttribute("y", &c.posY);
        position->QueryDoubleAttribute("z", &c.posZ);

        XMLElement *lookAt = camera->FirstChildElement("lookAt");
        lookAt->QueryDoubleAttribute("x", &c.lookAtX);
        lookAt->QueryDoubleAttribute("y", &c.lookAtY);
        lookAt->QueryDoubleAttribute("z", &c.lookAtZ);

        XMLElement *up = camera->FirstChildElement("up");
        up->QueryDoubleAttribute("x", &c.upX);
        up->QueryDoubleAttribute("y", &c.upY);
        up->QueryDoubleAttribute("z", &c.upZ);

        XMLElement *projection = camera->FirstChildElement("projection");
        projection->QueryDoubleAttribute("fov", &c.fov);
        projection->QueryDoubleAttribute("near", &c.near);
        projection->QueryDoubleAttribute("far", &c.far);


        //group
        XMLElement *group = root->FirstChildElement("group");
        XMLElement *models = group->FirstChildElement("models");



        for(XMLElement *model = models->FirstChildElement("model");model!=NULL;model = model->NextSiblingElement()) {

            const char *file;
            model->QueryStringAttribute("file",&file);
            char p[100] = "../../Models/";
            char *pathM = strcat(p, (char *) file);
            read3d(pathM);
        }


    }

}


void draw(){

    for(Triangle triangle:triangulos){
        triangle.drawTriangle();
    }
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

    //A posição inicial apresentada inicialmente a do xml,
    // depois com a interação com o teclado, a câmara torna-se "livre"
    GLfloat x = livre ? raio * cos(Beta) * sin(alfa) : c.posX;
    GLfloat y = livre ? raio * sin(Beta) : c.posY;
    GLfloat z = livre ? raio * cos(Beta) * cos(alfa) : c.posZ;



	gluLookAt(x,y,z,
		c.lookAtX, c.lookAtY, c.lookAtZ,
		c.upX,c.upY, c.upZ);

	//desenhar aqui
    glPolygonMode(GL_FRONT,GL_LINE);

    glBegin(GL_LINES);

    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);

    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glutPostRedisplay();
    glColor3f(1.0f, 1.0f, 1.0f);
    draw();

    glEnd();

	// End of frame
    glutSwapBuffers();
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
            raio--;
            break;
        case '-':
            livre = 1;
            raio++;
            break;
        case 'r':
            livre=0;
            raio=5;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {


    readXML(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    // enter GLUT's main cycle
    glutMainLoop();\


}