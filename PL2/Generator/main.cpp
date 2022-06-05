#include "main.h"

// using namespace tinyxml2;
using namespace std;

typedef struct point
{
    float x;
    float y;
    float z;
} point;

void triangleBuilder(point point1, point point1Norm, point point1texture,
                     point point2, point point2Norm, point point2texture,
                     point point3, point point3Norm, point point3texture, ofstream &f)
{
    f << point1.x << "," << point1.y << "," << point1.z << "," << point1Norm.x << "," << point1Norm.y << "," << point1Norm.z << "," << point1texture.x << "," << point1texture.y << endl;
    f << point2.x << "," << point2.y << "," << point2.z << "," << point2Norm.x << "," << point2Norm.y << "," << point2Norm.z << "," << point2texture.x << "," << point2texture.y << endl;
    f << point3.x << "," << point3.y << "," << point3.z << "," << point3Norm.x << "," << point3Norm.y << "," << point3Norm.z << "," << point3texture.x << "," << point3texture.y << endl;
    f.flush();
}

point reverseX(point point)
{
    point.x = -point.x;
    return point;
}

point reverseY(point point)
{
    point.y = -point.y;
    return point;
}

point reverseZ(point point)
{
    point.z = -point.z;
    return point;
}

point normalizeV(point p)
{
    if (p.x == 0 && p.y == 0 && p.z == 0)
    {
        return p;
    }
    float norm = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    p.x /= norm;
    p.y /= norm;
    p.z /= norm;
    return p;
}

// Function to create the triangles of the plane mesh given the number of divisions and the length of the plane
bool buildPlane(float length, float divisions, const char *filename)
{
    string ans = "";

    // Econtrar o numero de pontos total
    int totalPoints = 3 * divisions * divisions * 2;
    ans = to_string(totalPoints) + ",l\n";

    // Distancia entre cada ponto
    float divisory = length / (divisions);

    float start = length / 2;

    char pasta[30] = "../../PL2/Models/";
    ofstream out;
    out.open(strcat(pasta, filename));
    out << ans;

    point p1, p2, p3, p4;
    for (int i = 0; i < divisions; i++)
    {
        // out << "--- FILA ---" + to_string(i) + "\n";
        for (int j = 0; j < divisions; j++)
        {
            // out << "\n--- DIVISAO ---" + to_string(j) + "\n\n";
            p1 = point({-start + i * divisory,   // x
                        0,                       // y
                        -start + j * divisory}); // z

            p2 = point({-start + (i + 1) * divisory,
                        0,
                        -start + j * divisory});

            p3 = point({-start + (i + 1) * divisory,
                        0,
                        -start + (j + 1) * divisory});

            p4 = point({-start + i * divisory, 0,
                        -start + (j + 1) * divisory});

            // Normal Vector
            point normalBase = point({0, 1, 0});

            // Textures
            point text1 = point({(float)i / divisions, (float)j / divisions, 0});
            point text2 = point({(float)(i + 1) / divisions, (float)j / divisions, 0});
            point text3 = point({(float)(i + 1) / divisions, (float)(j + 1) / divisions, 0});
            point text4 = point({(float)i / divisions, (float)(j + 1) / divisions, 0});

            // Construir os Triangulos

            triangleBuilder(p1, normalBase, text1, p4, normalBase, text4, p2, normalBase, text2, out);
            triangleBuilder(p2, normalBase, text2, p4, normalBase, text4, p3, normalBase, text3, out);

            // triangleBuilder(p1, normalBase, text1, p2, normalBase, text2, p4, normalBase, text4, out);
            // triangleBuilder(p2, normalBase, text2,  p3, normalBase, text3, p4, normalBase, text4, out);
        }
    }
    out.close();
    return true;
}

// Function to create the triangles of the cube mesh given the number of divisions and the size of the cube
bool buildCube(float length, float divisions, const char *filename)
{
    string ans = "";

    // Econtrar o numero de pontos total
    int npontos = 6 * divisions * divisions * 2 * 3;
    ans = to_string(npontos) + ",l\n";

    // Distancia entre cada ponto
    float divisory = length / (divisions);

    float start = length / 2;

    char pasta[30] = "../../PL2/Models/";
    ofstream out;
    out.open(strcat(pasta, filename));
    out << ans;

    point p1, p2, p3, p4, p5, p6, p7, p8;
    // Criar os pontos
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {

            // -------------- BASE -------------- //

            point p1 = point({-start + i * divisory,   // x
                              -start,                  // y
                              -start + j * divisory}); // z

            point p2 = point({-start + (i + 1) * divisory,
                              -start,
                              -start + j * divisory});

            point p3 = point({-start + (i + 1) * divisory,
                              -start,
                              -start + (j + 1) * divisory});

            point p4 = point({-start + i * divisory,
                              -start,
                              -start + (j + 1) * divisory});

            // Normal Vector
            point normalBase = point({0, -1, 0});

            // Textures
            point text1 = point({(float)i / divisions, (float)j / divisions, 0});
            point text2 = point({(float)(i + 1) / divisions, (float)j / divisions, 0});
            point text3 = point({(float)(i + 1) / divisions, (float)(j + 1) / divisions, 0});
            point text4 = point({(float)i / divisions, (float)(j + 1) / divisions, 0});

            // Construir os Triangulos

            triangleBuilder(p1, normalBase, text1, p2, normalBase, text2, p4, normalBase, text4, out);
            triangleBuilder(p2, normalBase, text2, p3, normalBase, text3, p4, normalBase, text4, out);

            // -------------- TOPO -------------- //

            point p5 = reverseY(p1);
            point p6 = reverseY(p2);
            point p7 = reverseY(p3);
            point p8 = reverseY(p4);

            point normalTopo = reverseY(normalBase);

            triangleBuilder(p5, normalTopo, text1, p8, normalTopo, text4, p6, normalTopo, text2, out);
            triangleBuilder(p6, normalTopo, text2, p8, normalTopo, text4, p7, normalTopo, text3, out);

            // -------------- FRENTE -------------- //

            p1 = point({-start + i * divisory,
                        -start + j * divisory,
                        -start});

            p2 = point({-start + (i + 1) * divisory,
                        -start + j * divisory,
                        -start});

            p3 = point({-start + (i + 1) * divisory,
                        -start + (j + 1) * divisory,
                        -start});

            p4 = point({-start + i * divisory,
                        -start + (j + 1) * divisory,
                        -start});

            point normalFrente = point({0, 0, 1});

            triangleBuilder(p1, normalFrente, text1, p4, normalFrente, text4, p2, normalFrente, text2, out);
            triangleBuilder(p2, normalFrente, text2, p4, normalFrente, text4, p3, normalFrente, text3, out);

            // -------------- TRAS -------------- //

            p5 = reverseZ(p1);
            p6 = reverseZ(p2);
            p7 = reverseZ(p3);
            p8 = reverseZ(p4);

            point normalTras = reverseZ(normalFrente);

            triangleBuilder(p5, normalTras, text1, p6, normalTras, text2, p8, normalTras, text4, out);
            triangleBuilder(p6, normalTras, text2, p7, normalTras, text3, p8, normalTras, text4, out);

            // -------------- ESQUERDA -------------- //

            p1 = point({-start,
                        -start + i * divisory,
                        -start + j * divisory});

            p2 = point({-start,
                        -start + (i + 1) * divisory,
                        -start + j * divisory});

            p3 = point({-start,
                        -start + (i + 1) * divisory,
                        -start + (j + 1) * divisory});

            p4 = point({-start,
                        -start + i * divisory,
                        -start + (j + 1) * divisory});

            point normalEsquerda = point({-1, 0, 0});

            triangleBuilder(p1, normalEsquerda, text1, p4, normalEsquerda, text4, p2, normalEsquerda, text2, out);
            triangleBuilder(p2, normalEsquerda, text2, p4, normalEsquerda, text4, p3, normalEsquerda, text3, out);

            // -------------- DIREITA -------------- //

            p5 = reverseX(p1);
            p6 = reverseX(p2);
            p7 = reverseX(p3);
            p8 = reverseX(p4);

            point normalDireita = reverseX(normalEsquerda);

            triangleBuilder(p5, normalDireita, text1, p6, normalDireita, text2, p8, normalDireita, text4, out);
            triangleBuilder(p6, normalDireita, text2, p7, normalDireita, text3, p8, normalDireita, text4, out);
        }
    }

    out.close();
    return true;
}

// Funcao responsavel por obter os triangulos para a construcao de um cone dados os parametros
bool buildCone(float radius, float height, int slices, int stacks, char *filename)
{

    string ans = to_string((2 * slices * stacks) * 3) + ",l" + "\n";

    // Altura de cada stack
    float stackHeight = height / stacks;

    // Calcula coordenadas para cada circunferencia
    for (float i = 0; i < stacks; i++)
    {

        // Os raios das stacks inferior e superior que vao conter os pontos
        float stackRadius = ((radius * (height - (stackHeight * i))) / height);
        float stackRadius2 = ((radius * (height - (stackHeight * (i + 1)))) / height);

        // Angulo entre cada ponto (orientado horizontalmente)
        float alfa = (2 * M_PI) / slices;

        // Construir os triangulos dos lados
        for (int j = 0; j < slices; j++)
        {
            // Angulo onde o ponto se situa de acordo com a sua posicao
            float anglePonto1 = alfa * j;
            float anglePonto2 = alfa * (j + 1);

            // Primeiro Ponto da slice no stack Inferior
            float pontoStack11x = cos(anglePonto1) * stackRadius;
            float pontoStack11y = stackHeight * i;
            float pontoStack11z = -sin(anglePonto1) * stackRadius;

            // Segundo Ponto da slice no stack Inferior
            float pontoStack12x = cos(anglePonto2) * stackRadius;
            float pontoStack12y = stackHeight * i;
            float pontoStack12z = -sin(anglePonto2) * stackRadius;

            // Primeiro Ponto da slice no stack Superior
            float pontoStack23x = cos(anglePonto1) * stackRadius2;
            float pontoStack23y = stackHeight * (i + 1);
            float pontoStack23z = -sin(anglePonto1) * stackRadius2;

            // Segundo Ponto da slice no stack Superior
            float pontoStack24x = cos(anglePonto2) * stackRadius2;
            float pontoStack24y = stackHeight * (i + 1);
            float pontoStack24z = -sin(anglePonto2) * stackRadius2;

            float dinf = stackRadius * (height / radius);
            float dsup = stackRadius2 * (height / radius);

            point p1 = {pontoStack11x, pontoStack11y, pontoStack11z};
            point p2 = {pontoStack12x, pontoStack12y, pontoStack12z};
            point p3 = {pontoStack23x, pontoStack23y, pontoStack23z};
            point p4 = {pontoStack24x, pontoStack24y, pontoStack24z};

            point p1Norm = normalizeV({pontoStack11x, dinf, pontoStack11z});
            point p2Norm = normalizeV({pontoStack12x, dinf, pontoStack12z});
            point p3Norm = normalizeV({pontoStack23x, dsup, pontoStack23z});
            point p4Norm = normalizeV({pontoStack24x, dsup, pontoStack24z});

            // Textures
            float tx1 = (float) j  / slices;
            float ty1 = 1.0f - ((float) i / stacks);

            float tx2 = (float) j / slices;
            float ty2 = 1.0f - (float) (i + 1) / stacks;

            float tx3 = (float) (j + 1) / slices;
            float ty3 = 1.0f - (float) (i + 1) / stacks;

            float tx4 = (float)(j + 1) / slices;
            float ty4 = 1.0f - (float) i / stacks;

            string point1 = to_string(pontoStack11x) + "," + to_string(pontoStack11y) + "," + to_string(pontoStack11z) + ",";
            string point1Norm = to_string(p1Norm.x) + "," + to_string(p1Norm.y) + "," + to_string(p1Norm.z) + ",";
            string texture1 = to_string(tx1) + "," + to_string(ty1) + "\n";

            string point2 = to_string(pontoStack12x) + "," + to_string(pontoStack12y) + "," + to_string(pontoStack12z) + ",";
            string point2Norm = to_string(p2Norm.x) + "," + to_string(p2Norm.y) + "," + to_string(p2Norm.z) + ",";
            string texture2 = to_string(tx2) + "," + to_string(ty2) + "\n";

            string point3 = to_string(pontoStack23x) + "," + to_string(pontoStack23y) + "," + to_string(pontoStack23z) + ",";
            string point3Norm = to_string(p3Norm.x) + "," + to_string(p3Norm.y) + "," + to_string(p3Norm.z) + ",";
            string texture3 = to_string(tx3) + "," + to_string(ty3) + "\n";

            string point4 = to_string(pontoStack24x) + "," + to_string(pontoStack24y) + "," + to_string(pontoStack24z) + ",";
            string point4Norm = to_string(p4Norm.x) + "," + to_string(p4Norm.y) + "," + to_string(p4Norm.z) + ",";
            string texture4 = to_string(tx4) + "," + to_string(ty4) + "\n";

            if (i == 0)
            {
                // Construir os triangulos adjacentes a base e o triangulo que contem
                // Constroi tambem o triangulo que contem os pontos na stack inferior e o centro
                string base = "0.000000,0.000000,0.000000,";
                string baseNorm = "0.000000,-1.000000,0.000000,";
                string textureBase = "0,0\n";

                ans = ans + point3 + point3Norm + texture3 + point1 + point1Norm + texture1 + point2 + point2Norm + texture2 + point2 + point2Norm + texture2 + point4 + point4Norm + texture4 + point3 + point3Norm + texture3;
                ans = ans + base + baseNorm + textureBase + point2 + point2Norm + texture2 + point1 + point1Norm + texture1;
            }
            // Enquanto nao for o ultimo stack
            else if (i != (stacks - 1))
            {
                // Ordenar os triangulos e adicionar a resposta
                ans = ans + point3 + point3Norm + texture3 + point1 + point1Norm + texture1 + point2 + point2Norm + texture2 + point2 + point2Norm + texture2 + point4 + point4Norm + texture4 + point3 + point3Norm + texture3;
            }
            else
                // Triangulo da ultima stack - o point 3 e o point 4 coincidem, sendo correspondentes ao vertice do topo do cone
                ans = ans + point3 + "0,1,0," + texture3 + point1 + point1Norm + texture1 + point2 + point2Norm + texture2;
        }
    }

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();
    return true;
}

// Funcao responsavel por obter os triangulos para a construcao de uma esfera dados os parametros
bool buildSphere(float radius, int slices, int stacks, char *filename)
{

    int npontos = 6 * slices * (stacks - 1);
    string ans = to_string(npontos) + ",l" + "\n";

    // angulo interno de cada slice
    float alfa = (2 * M_PI) / slices;

    // angulo interno decada stack
    float beta = M_PI / stacks;

    float sliceStep, sliceStep2, stackStep, stackStep2;

    for (int i = 0; i < stacks; i++)
    {
        stackStep = (M_PI / 2) - i * beta;
        stackStep2 = (M_PI / 2) - (i + 1) * beta;

        for (int j = 0; j < slices; j++)
        {

            sliceStep = j * alfa;
            sliceStep2 = (j + 1) * alfa;

            // Point Coordinates
            float x1 = cos(stackStep) * sin(sliceStep) * radius;
            float y1 = sin(stackStep) * radius;
            float z1 = cos(stackStep) * cos(sliceStep) * radius;

            float x2 = cos(stackStep2) * sin(sliceStep) * radius;
            float y2 = sin(stackStep2) * radius;
            float z2 = cos(stackStep2) * cos(sliceStep) * radius;

            float x3 = cos(stackStep2) * sin(sliceStep2) * radius;
            float y3 = sin(stackStep2) * radius;
            float z3 = cos(stackStep2) * cos(sliceStep2) * radius;

            float x4 = cos(stackStep) * sin(sliceStep2) * radius;
            float y4 = sin(stackStep) * radius;
            float z4 = cos(stackStep) * cos(sliceStep2) * radius;

            // Normals
            point normal1 = normalizeV({x1, y1, z1});
            point normal2 = normalizeV({x2, y2, z2});
            point normal3 = normalizeV({x3, y3, z3});
            point normal4 = normalizeV({x4, y4, z4});

            // Textures
            float tx1 = (float) j  / slices;
            float ty1 = 1.0f - ((float) i / stacks);

            float tx2 = (float) j / slices;
            float ty2 = 1.0f - (float) (i + 1) / stacks;

            float tx3 = (float) (j + 1) / slices;
            float ty3 = 1.0f - (float) (i + 1) / stacks;

            float tx4 = (float)(j + 1) / slices;
            float ty4 = 1.0f - (float) i / stacks;

            if (i != 0)
            {
                // Coordenadas dos pontos, normais e texturas para desenhar o triangulo pela ordem correta
                // Ponto 1
                ans = ans + to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + ",";
                ans = ans + to_string(normal1.x) + "," + to_string(normal1.y) + "," + to_string(normal1.z) + ",";
                ans = ans + to_string(tx1) + "," + to_string(ty1) + "\n";

                // Ponto 2
                ans = ans + to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + ",";
                ans = ans + to_string(normal2.x) + "," + to_string(normal2.y) + "," + to_string(normal2.z) + ",";
                ans = ans + to_string(tx2) + "," + to_string(ty2) + "\n";

                // Ponto 4
                ans = ans + to_string(x4) + "," + to_string(y4) + "," + to_string(z4) + ",";
                ans = ans + to_string(normal4.x) + "," + to_string(normal4.y) + "," + to_string(normal4.z) + ",";
                ans = ans + to_string(tx4) + "," + to_string(ty4) + "\n";
            }

            if (i != stacks - 1)
            {
                // Ponto 2
                ans = ans + to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + ",";
                ans = ans + to_string(normal2.x) + "," + to_string(normal2.y) + "," + to_string(normal2.z) + ",";
                ans = ans + to_string(tx2) + "," + to_string(ty2) + "\n";

                // Ponto 3
                ans = ans + to_string(x3) + "," + to_string(y3) + "," + to_string(z3) + ",";
                ans = ans + to_string(normal3.x) + "," + to_string(normal3.y) + "," + to_string(normal3.z) + ",";
                ans = ans + to_string(tx3) + "," + to_string(ty3) + "\n";

                // Ponto 4
                ans = ans + to_string(x4) + "," + to_string(y4) + "," + to_string(z4) + ",";
                ans = ans + to_string(normal4.x) + "," + to_string(normal4.y) + "," + to_string(normal4.z) + ",";
                ans = ans + to_string(tx4) + "," + to_string(ty4) + "\n";
            }
        }
    }

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();

    return true;
}

// Calcular as coordenadas de cada ponto seguindo as formulas de bezier
float *formulaBezier(float t, float *cpoint1, float *cpoint2, float *cpoint3, float *cpoint4)
{

    float temp = 1.0 - t;
    float *ans = new float[3];

    float point1 = temp * temp * temp;
    float point2 = 3 * t * temp * temp;
    float point3 = 3 * t * t * temp;
    float point4 = t * t * t;

    // Calcular o xyz respetivamente do ponto
    ans[0] = (point1 * cpoint1[0]) + (point2 * cpoint2[0]) + (point3 * cpoint3[0]) + (point4 * cpoint4[0]);
    ans[1] = (point1 * cpoint1[1]) + (point2 * cpoint2[1]) + (point3 * cpoint3[1]) + (point4 * cpoint4[1]);
    ans[2] = (point1 * cpoint1[2]) + (point2 * cpoint2[2]) + (point3 * cpoint3[2]) + (point4 * cpoint4[2]);

    return ans;
}

// Calcular as coordenadas de cada ponto nas curvas de bezier chamando a funcao com a formula
float *buildBezierCurve(float a, float b, float **points, int *index)
{

    // Calcula os pontos de controlo
    float *pointsB = new float[3];

    // Armazenar as coordenadas dos pontos de controlo
    float controlPoints[4][3];
    // Armazenar as coordenadas para calcular o ponto objetivo
    float ans[4][3];

    // Variaveis de ciclo
    int j = 0, x = 0, i;

    // Criar a matriz com as coordenadas de todos os pontos de controlo
    for (i = 0; i < 16; i++)
    {
        controlPoints[j][0] = points[index[i]][0];
        controlPoints[j][1] = points[index[i]][1];
        controlPoints[j][2] = points[index[i]][2];

        j++;
        if (j % 4 == 0)
        {
            pointsB = formulaBezier(a, controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]);
            ans[x][0] = pointsB[0];
            ans[x][1] = pointsB[1];
            ans[x][2] = pointsB[2];
            x++;
            j = 0;
        }
    }

    float *res = formulaBezier(b, ans[0], ans[1], ans[2], ans[3]);
    // res = formulaB(b, ans[0], ans[1], ans[2], ans[3]);
    return res;
}

point crossProduct(point vector1, point vector2)
{
    point ans;
    ans.x = vector1.y * vector2.z - vector1.z * vector2.y;
    ans.y = vector1.z * vector2.x - vector1.x * vector2.z;
    ans.z = vector1.x * vector2.y - vector1.y * vector2.x;

    return ans;
}

vector<point> buildPatch(string inputfile, int tesselation)
{
    // Iniciar leitura do ficheiro
    ifstream read(inputfile);
    string line, aux;

    // Vector com os pontos ordenados para escrever no ficheiro
    vector<point> orderedPoints;
    vector<point> orderedNormals;
    vector<point> orderedTexture;

    // Variaveis para controlar a leitura
    int next;
    float inc = 1.0 / tesselation;

    // Comecar a leitura do ficheiro
    getline(read, line);

    // Ler a primeira linha que contem o numero de patches
    int numberOfPatches = atoi(line.c_str());

    // Criar uma matriz com os indices de todos os patches -> cada linha contem os indices de um patch
    int **indexes = new int *[numberOfPatches];

    for (int i = 0; i < numberOfPatches; i++)
    {
        // Provavelmente o parser pode ser simplificado sem usar o erase, usando strtok ou algo do genero
        getline(read, line);
        indexes[i] = new int[16];
        for (int j = 0; j < 16; j++)
        {
            // Encontrar os indices que estao separados pelas virgulas
            next = line.find(",");
            aux = line.substr(0, next);
            // Armazenar o valor do indice
            indexes[i][j] = atoi(aux.c_str());
            line.erase(0, next + 1);
        }
    }

    // Ler o numero de pontos totais a serem lidos para desenhar a figura
    getline(read, line);
    int controlPoints = atoi(line.c_str());

    // Criar uma matriz com todos os pontos de controlo
    float **points = new float *[controlPoints];

    // Leitura final do ficheiro
    for (int i = 0; i < controlPoints; i++)
    {
        // Ler a linha
        getline(read, line);

        // Criar um array com 3 floats para guardar as coordenadas de cada ponto
        points[i] = new float[3];
        for (int j = 0; j < 3; j++)
        {
            next = line.find(",");
            aux = line.substr(0, next);
            points[i][j] = atof(aux.c_str());
            line.erase(0, next + 1);
        }
    }

    float ***pointsResult = new float **[numberOfPatches];
    // Calcular as coordenadas dos pontos para desenhar a figura
    for (int i = 0; i < numberOfPatches; i++)
    {
        //
        pointsResult[i] = new float *[4];
        for (int x = 0; x < tesselation; x++)
        {
            for (int y = 0; y < tesselation; y++)
            {
                float x1 = inc * x;
                float x2 = inc * (x + 1);
                float y1 = inc * y;
                float y2 = inc * (y + 1);

                // Calcular as coordenadas dos pontos da face por desenhar
                pointsResult[i][0] = buildBezierCurve(x1, y1, points, indexes[i]);
                pointsResult[i][1] = buildBezierCurve(x1, y2, points, indexes[i]);
                pointsResult[i][2] = buildBezierCurve(x2, y1, points, indexes[i]);
                pointsResult[i][3] = buildBezierCurve(x2, y2, points, indexes[i]);

                // Formar os pares de triangulos com as coordenadas ordenadas
                // Primeiro triangulo
                point p1 = {pointsResult[i][0][0], pointsResult[i][0][1], pointsResult[i][0][2]};
                point p2 = {pointsResult[i][2][0], pointsResult[i][2][1], pointsResult[i][2][2]};
                point p3 = {pointsResult[i][3][0], pointsResult[i][3][1], pointsResult[i][3][2]};

                // Adicionar as coordenadas em ordem de cada ponto ao vetor de resposta
                orderedPoints.push_back(p1);
                orderedPoints.push_back(p2);
                orderedPoints.push_back(p3);

                // Calcular as normais a cada ponto
                point v1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
                point v2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
                point normal1 = crossProduct(v1, v2);

                point v3 = {p3.x - p2.x, p3.y - p2.y, p3.z - p2.z};
                point v4 = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
                point normal2 = crossProduct(v3, v4);

                point v5 = {p1.x - p3.x, p1.y - p3.y, p1.z - p3.z};
                point v6 = {p2.x - p3.x, p2.y - p3.y, p2.z - p3.z};
                point normal3 = crossProduct(v5, v6);

                normal1 = normalizeV(normal1);
                normal2 = normalizeV(normal2);
                normal3 = normalizeV(normal3);

                // Adicionar as normais em ordem de cada ponto ao vetor de resposta
                orderedNormals.push_back(normal1);
                orderedNormals.push_back(normal2);
                orderedNormals.push_back(normal3);

                // Adicionar as coordenadas das texturas em ordem de cada ponto ao vetor de resposta
                point texture1 = {x1, y1};
                point texture2 = {x1, y2};
                point texture3 = {x2, y1};
                point texture4 = {x2, y2};

                orderedTexture.push_back(texture2);
                orderedTexture.push_back(texture1);
                orderedTexture.push_back(texture3);
                orderedTexture.push_back(texture1);
                orderedTexture.push_back(texture2);
                orderedTexture.push_back(texture4);

                // Segundo Triangulo
                point p4 = {pointsResult[i][0][0], pointsResult[i][0][1], pointsResult[i][0][2]};
                point p5 = {pointsResult[i][3][0], pointsResult[i][3][1], pointsResult[i][3][2]};
                point p6 = {pointsResult[i][1][0], pointsResult[i][1][1], pointsResult[i][1][2]};

                orderedPoints.push_back(p4);
                orderedPoints.push_back(p5);
                orderedPoints.push_back(p6);

                // Calcular as normais para o segunto triangulo
                point v7 = {p5.x - p4.x, p5.y - p4.y, p5.z - p4.z};
                point v8 = {p6.x - p4.x, p6.y - p4.y, p6.z - p4.z};
                point normal4 = crossProduct(v7, v8);

                point v9 = {p6.x - p5.x, p6.y - p5.y, p6.z - p5.z};
                point v10 = {p4.x - p5.x, p4.y - p5.y, p4.z - p5.z};
                point normal5 = crossProduct(v9, v10);

                point v11 = {p4.x - p6.x, p4.y - p6.y, p4.z - p6.z};
                point v12 = {p5.x - p6.x, p5.y - p6.y, p5.z - p6.z};
                point normal6 = crossProduct(v11, v12);

                normal4 = normalizeV(normal4);
                normal5 = normalizeV(normal5);
                normal6 = normalizeV(normal6);

                orderedNormals.push_back(normal4);
                orderedNormals.push_back(normal5);
                orderedNormals.push_back(normal6);
            }
        }
    }
    read.close();

    int nPoints = orderedPoints.size();
    printf("%d\n", nPoints);
    ofstream out;
    out.open("../Models/bezier_nt.3d");
    out << nPoints << ",l\n";
    for (int i = 0; i < nPoints + 1; i++)
    {
        out << to_string(orderedPoints[i].x) << "," << orderedPoints[i].y << "," << orderedPoints[i].z << ",";
        out << to_string(orderedNormals[i].x) << "," << orderedNormals[i].y << "," << orderedNormals[i].z << ",";
        out << to_string(orderedTexture[i].x) << "," << orderedTexture[i].y << "\n";
    }
    out.flush();
    out.close();
    return orderedPoints;
}

int main(int argc, char **argv)
{
    // char *objeto = argv[1];

    // if (strcmp(objeto, "cone") == 0)
    // {
    //     buildCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    // }
    // else if (strcmp(objeto, "sphere") == 0)
    // {
    //     buildSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
    // }
    // else if (strcmp(objeto, "box") == 0)
    // {
    //     buildCube(atof(argv[2]), atof(argv[3]), argv[4]);
    // }
    // else
    // {
    //     buildPlane(atof(argv[2]), atof(argv[3]), argv[4]);
    // }
    char namefile2[20] = "cone_nt.3d";
    // buildSphere(1, 10, 10, namefile2);
    buildCone(1, 2, 10, 10, namefile2);
    // buildPlane(1, 3, namefile2);
    // buildCube(2, 3, namefile2);
    // const char namefile[35] = "../test_files_phase_3/teapot.patch";
    // buildPatch(namefile, 10);
}
