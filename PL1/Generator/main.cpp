#include "main.h"

// using namespace tinyxml2;
using namespace std;

typedef struct point
{
    float x;
    float y;
    float z;
} point;

string buildTriangles(vector<vector<point>> &matrix, int div)
{

    string ans = "";
    string temp;

    for (int i = 0; i < div - 1; i++)
    {
        temp = "";
        for (int j = 0; j < div - 1; j++)
        {
            temp = to_string(matrix[i + 1][j].x) + "," + to_string(matrix[i + 1][j].y) + "," + to_string(matrix[i + 1][j].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i][j].x) + "," + to_string(matrix[i][j].y) + "," + to_string(matrix[i][j].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i][j + 1].x) + "," + to_string(matrix[i][j + 1].y) + "," + to_string(matrix[i][j + 1].z) + "\n";

            ans += temp;

            temp = to_string(matrix[i][j + 1].x) + "," + to_string(matrix[i][j + 1].y) + "," + to_string(matrix[i][j + 1].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i + 1][j + 1].x) + "," + to_string(matrix[i + 1][j + 1].y) + "," + to_string(matrix[i + 1][j + 1].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i + 1][j].x) + "," + to_string(matrix[i + 1][j].y) + "," + to_string(matrix[i + 1][j].z) + "\n";

            ans += temp;

            // temp = ans << "\nTriangulo\n";
        }
    }
    return ans;
}

/**
 * Funcao que escreve os triangulos a partir de uma matriz de forma inversa
 * @param matrix matriz que vai conter todos os vertices para construir os triangulos
 * @return string com as coisas ansultantes?
 */
string buildTrianglesInv(vector<vector<point>> &matrix, int div)
{

    string ans = "";
    string temp;

    for (int i = 0; i < div - 1; i++)
    {
        temp = "";
        for (int j = 0; j < div - 1; j++)
        {
            temp = to_string(matrix[i][j + 1].x) + "," + to_string(matrix[i][j + 1].y) + "," + to_string(matrix[i][j + 1].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i][j].x) + "," + to_string(matrix[i][j].y) + "," + to_string(matrix[i][j].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i + 1][j].x) + "," + to_string(matrix[i + 1][j].y) + "," + to_string(matrix[i + 1][j].z) + "\n";

            ans += temp;

            temp = to_string(matrix[i + 1][j].x) + "," + to_string(matrix[i + 1][j].y) + "," + to_string(matrix[i + 1][j].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i + 1][j + 1].x) + "," + to_string(matrix[i + 1][j + 1].y) + "," + to_string(matrix[i + 1][j + 1].z) + "\n";

            ans += temp;
            temp = to_string(matrix[i][j + 1].x) + "," + to_string(matrix[i][j + 1].y) + "," + to_string(matrix[i][j + 1].z) + "\n";

            ans += temp;

            // temp = ans << "\nTriangulo\n";
        }
    }
    return ans;
}

/**
 * Funcao que cria um Cubo
 * @return nao sei ainda
 */
bool buildCube(float length, float divisions, char *filename)
{
    // Criar uma outra funcao capaz de criar planos e arrumar as coordenadas
    // seguindo o mesmo padrao de construir um so plano, cada plano sera uma
    // matriz que facilmente se vai ordenar.

    // Provavelmente vai ser necessario construir em paralelo os planos
    // Os planos paralelos a XZ vao ter as mesmas coordenadas x e z e o y
    // ira ser alterado para a altura do triangulo
    //
    // Os planos paralelos a YZ terao as mesmas coordenadas em Y e Z
    // O x sera o mesmo mas simetrico e em modulo sera length/2
    //
    // Os planos paralelos a XY terao as mesmas coordenadas em X e Y
    // O z sera o mesmo mas simetrico e em modulo sera length/2

    string ans = "";

    float px1, px2, py1, py2, pz1, pz2;
    // planos paralelos ao ZY
    px1 = length / 2;
    px2 = -px1;

    // planos paralelos ao XY
    pz1 = px1;
    pz2 = -pz1;

    // Planos paralelos ao XZ
    py1 = px1;
    py2 = -py1;

    // Econtrar o numero de pontos total
    divisions += 1;
    int npontos = 6 * divisions * divisions;
    ans = to_string(npontos) + "\n";

    // Distancia entre cada ponto
    float divisory = length / (divisions - 1);

    // Criar a matriz com os pontos dos planos paralelos ao ZY
    // Matriz que vai conter todos os pontos
    vector<vector<point>> matrixPos;
    vector<vector<point>> matrixNeg;

    // Calculamos as coordenadas dos dois planos paralelos ao mesmo tempo
    // Sabemos que o X e o Z dos planos serao simetricos
    // O X e constante e dado por px1 e px2
    float startz = -px1;
    float starty = px1;

    // point tempPos = {px1, starty, startz};
    // point tempNeg = {px2, starty, startz};

    for (int i = 0; i < divisions; i++)
    {
        vector<point> tempVectorPos;
        vector<point> tempVectorNeg;
        for (int j = 0; j < divisions; j++)
        {
            point tempPos = {px1, starty, startz + (j * divisory)};
            point tempNeg = {px2, starty, startz + (j * divisory)};
            tempVectorPos.push_back(tempPos);
            tempVectorNeg.push_back(tempNeg);
        }
        starty -= divisory;
        matrixPos.push_back(tempVectorPos);
        matrixNeg.push_back(tempVectorNeg);
    }

    ans += buildTrianglesInv(matrixNeg, divisions);
    ans += buildTriangles(matrixPos, divisions);

    /////////////////////////////////////
    // Calcular os planos paralelos a XY//
    /////////////////////////////////////

    float startx = px1;
    starty = py1;

    // tempPos = {startx, starty, pz1};
    // tempNeg = {startx, starty, pz2};

    matrixPos.clear();
    matrixNeg.clear();

    // Colocar os pontos na matriz
    for (int i = 0; i < divisions; i++)
    {
        // percorrer as linhas
        vector<point> tempVectorPos;
        vector<point> tempVectorNeg;
        for (int j = 0; j < divisions; j++)
        {
            point tempPos = {startx - (j * divisory), starty, pz1};
            point tempNeg = {startx - (j * divisory), starty, pz2};
            tempVectorPos.push_back(tempPos);
            tempVectorNeg.push_back(tempNeg);
        }
        matrixPos.push_back(tempVectorPos);
        matrixNeg.push_back(tempVectorNeg);
        starty -= divisory;
    }

    ans += buildTrianglesInv(matrixNeg, divisions);
    ans += buildTriangles(matrixPos, divisions);

    //////////////////////////////////////
    // Calcular os planos paralelos a XZ//
    //////////////////////////////////////

    startx = px1;
    startz = -startx;

    // tempPos = {startx, py2, startz};
    // tempNeg = {startx, py1, startz};

    matrixPos.clear();
    matrixNeg.clear();

    // Colocar os pontos na matriz
    for (int i = 0; i < divisions; i++)
    {
        // percorrer as linhas
        vector<point> tempVectorPos;
        vector<point> tempVectorNeg;
        for (int j = 0; j < divisions; j++)
        {
            point tempPos = {startx - (j * divisory), py1, startz};
            point tempNeg = {startx - (j * divisory), py2, startz};
            tempVectorPos.push_back(tempPos);
            tempVectorNeg.push_back(tempNeg);
        }
        matrixPos.push_back(tempVectorPos);
        matrixNeg.push_back(tempVectorNeg);
        startz += divisory;
    }

    ans += buildTriangles(matrixPos, divisions);
    ans += buildTrianglesInv(matrixNeg, divisions);

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();

    return true;
}

/**
 * Funcao que cria um plano em XZ
 * @param length length do plano
 * @param divisions numero de subdivisoes por lado
 * @return nao sei ainda
 */
bool buildPlane(float length, int divisions, char *filename)
{

    string ans = "";

    // Inputs Errados
    if (length < 0 || divisions < 0)
        return false;

    divisions += 1;
    int npontos = divisions * divisions;
    ans = to_string(npontos) + "\n";

    // criar uma matriz com as coordenadas de todos os pontos
    vector<vector<point>> matrix;

    float divisory = length / (divisions - 1);
    float startx = length / 2;
    float startz = startx;
    point temp = {startx, 0, startz};

    // Colocar os pontos na matriz
    for (int i = 0; i < divisions; i++)
    { // percorrer as linhas
        vector<point> tempV;
        for (int j = 0; j < divisions; j++)
        {
            temp.x = startx - (j * divisory);
            tempV.push_back(temp);
        }
        matrix.push_back(tempV);
        startz -= divisory;
        temp.z = startz;
    }

    ans += buildTrianglesInv(matrix, divisions);

    // funcao que ordena as coordenadas da matriz por triangulos

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();

    return true;
}

/**
 * Funcao responsavel por obter os triangulos para a construcao de um cone dados os parametros
 * @param radius raio da base do cone
 * @param height altura do cone
 * @param slices numero de cortes no plano horizontal
 * @param stacks numero de cones no plano vertical
 * @return string com o resultado ou talvez um file idk
 */
bool buildCone(float radius, float height, int slices, int stacks, char *filename)
{

    string ans = to_string((2 * slices * stacks) * 3) + "\n";

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
        for (int c = 0; c < slices; c++)
        {
            // Angulo onde o ponto se situa de acordo com a sua posicao
            float anglePonto1 = alfa * c;
            float anglePonto2 = alfa * (c + 1);

            // Primeiro Ponto da slice no stack INferior
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

            string p1 = to_string(pontoStack11x) + "," + to_string(pontoStack11y) + "," + to_string(pontoStack11z) + "\n";
            string p2 = to_string(pontoStack12x) + "," + to_string(pontoStack12y) + "," + to_string(pontoStack12z) + "\n";
            string p3 = to_string(pontoStack23x) + "," + to_string(pontoStack23y) + "," + to_string(pontoStack23z) + "\n";
            string p4 = to_string(pontoStack24x) + "," + to_string(pontoStack24y) + "," + to_string(pontoStack24z) + "\n";

            if (i == 0)
            {
                // Construir os triangulos adjacentes a base e o triangulo que contem
                // Constroi tambem o triangulo que contem os pontos na stack inferior e o centro
                string base = "0.000000,0.000000,0.000000\n";
                ans = ans + p3 + p1 + p2 + p2 + p4 + p3;
                ans = ans + base + p2 + p1;
            }
            // Enquanto nao for o ultimo stack
            else if (i != (stacks - 1))
            {
                ans = ans + p3 + p1 + p2 + p2 + p4 + p3; // Ordenar os triangulos e adicionar a resposta
            }
            else
                ans = ans + p3 + p1 + p2; // Triangulo da ultima stack
        }
    }

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();
    return true;
}

/**
 * Funcao responsavel por obter os triangulos para a construcao de uma esfera dados os parametros
 * @param radius raio da base do cone
 * @param height altura do cone
 * @param slices numero de cortes no plano horizontal
 * @param stacks numero de cones no plano vertical
 * @return string com o resultado ou talvez um file idk
 */
bool buildSphere(float radius, int slices, int stacks, char *filename)
{

    int npontos = 6 * slices * (stacks - 1);
    string ans = to_string(npontos) + "\n";

    // angulo interno de cada slice
    float alfa = (2 * M_PI) / slices;

    // Altura de cada corte na vertical
    float stackHeight = (2 * radius) / stacks;

    // Calcula coordenadas para cada circunferencia
    for (float i = radius; i > 0.000001; i -= stackHeight)
    {

        float stackRadius = sqrt(pow(radius, 2) - pow(i, 2));
        float stackRadius2 = sqrt(pow(radius, 2) - pow((i - stackHeight), 2));

        for (int c = 0; c < slices; c++)
        {

            // Angulo onde o ponto se situa de acordo com a sua posicao
            float anglePonto1 = alfa * c;
            float anglePonto2 = alfa * (c + 1);

            float pontoStack11x = cos(anglePonto1) * stackRadius;
            float pontoStack11y = i;
            float pontoStack11z = -sin(anglePonto1) * stackRadius;

            float pontoStack12x = cos(anglePonto2) * stackRadius;
            float pontoStack12z = -sin(anglePonto2) * stackRadius;

            float pontoStack23x = cos(anglePonto1) * stackRadius2;
            float pontoStack23y = (i - stackHeight);
            float pontoStack23z = -sin(anglePonto1) * stackRadius2;

            float pontoStack24x = cos(anglePonto2) * stackRadius2;
            float pontoStack24z = -sin(anglePonto2) * stackRadius2;

            string coordinatesYMinus = to_string((-1 * i));
            string coordinatesY3Minus = to_string((-1 * (i - stackHeight)));

            string p1 = to_string(pontoStack11x) + "," + to_string(pontoStack11y) + "," + to_string(pontoStack11z) + "\n";
            string p2 = to_string(pontoStack12x) + "," + to_string(pontoStack11y) + "," + to_string(pontoStack12z) + "\n";
            string p3 = to_string(pontoStack23x) + "," + to_string(pontoStack23y) + "," + to_string(pontoStack23z) + "\n";
            string p4 = to_string(pontoStack24x) + "," + to_string(pontoStack23y) + "," + to_string(pontoStack24z) + "\n";

            string p1Minus = to_string(pontoStack11x) + "," + to_string((-1 * i)) + "," + to_string(pontoStack11z) + "\n";
            string p2Minus = to_string(pontoStack12x) + "," + to_string((-1 * i)) + "," + to_string(pontoStack12z) + "\n";
            string p3Minus = to_string(pontoStack23x) + "," + coordinatesY3Minus + "," + to_string(pontoStack23z) + "\n";
            string p4Minus = to_string(pontoStack24x) + "," + coordinatesY3Minus + "," + to_string(pontoStack24z) + "\n";

            // construir os lados da esfera
            if (i != radius)
            {
                // construir os triangulos da parte superior
                ans = ans + p1 + p3 + p4 + p1 + p4 + p2;
                // construir os triangulos simetricos ao plano horizontal
                if (!((stacks % 2 != 0) && (i - stackHeight) < 0))
                    ans = ans + p1Minus + p2Minus + p3Minus + p2Minus + p4Minus + p3Minus;
            }
            // Os "polos" da esfera
            else
            {
                ans = ans + p1 + p3 + p4;
                ans = ans + p3Minus + p1Minus + p4Minus;
            }
        }
    }

    char pasta[30] = "../Models/";
    ofstream out(strcat(pasta, filename));
    out << ans;
    out.close();

    return true;
}

int main(int argc, char **argv)
{
    char *objeto = argv[1];

    if (strcmp(objeto, "cone") == 0)
    {
        buildCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    }
    else if (strcmp(objeto, "sphere") == 0)
    {
        buildSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
    }
    else if (strcmp(objeto, "box") == 0)
    {
        buildCube(atof(argv[2]), atof(argv[3]), argv[4]);
    }
    else
    {
        buildPlane(atof(argv[2]), atof(argv[3]), argv[4]);
    }
    // buildSphere(1, 10, 10);
    // buildCone(1, 2, 8, 3);
    // buildPlane(2,2);
    // buildCube(2, 3);
}
