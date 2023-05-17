#include "etapa5.h"

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
bool displayWired = true;
unsigned char fig = '1';

// Eye position
float eyeXDirection = 2.0f;
float eyeYDirection = 2.0f;
float eyeZDirection = 2.0f;
// Look-at position
float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;
// Up vector
float upX = 0.0f;
float upY = 1.0f;
float upZ = 0.0f;
// Light colors
GLfloat l1[] = {PURE_BLACK_ALPHA};
GLfloat l2[] = {PURE_BLACK_ALPHA};
GLfloat l3[] = {PURE_BLACK_ALPHA};
GLfloat l4[] = {PURE_BLACK_ALPHA};
//
GLfloat posl1[] = {3.0f, 3.0f, 3.0f, 0.0f};
GLfloat ambient[] = {PURE_BLACK_ALPHA};
GLfloat diff[] = {PURE_WHITE_ALPHA};
GLfloat spct[] = {PURE_WHITE};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyeXDirection, eyeYDirection, eyeZDirection, // Eye position
              lookAtX, lookAtY, lookAtZ,                   // Look-at position
              upX, upY, upZ);                              // Up vector

    float rotationCoords[] = {0.0f, 1.0f, 0.0f};
    struct Color3f figColor;
    figColor.r = 0.251;
    figColor.g = 0.51f;
    figColor.b = 0.427f;
    switch (fig)
    {
    case '1':
        drawTeapot(0.5 * ESCALADO_FIG, 0, rotationCoords, displayWired, figColor);
        break;
    case '2':
        drawDonut(0.5 * ESCALADO_FIG, 20, 0, rotationCoords, displayWired, figColor);
        break;
    default:
        break;
    }

    if (displayPlane)
    {
        drawPlanes(ESCALADO_FIG);
    }

    if (displayAxis)
    {
        draw3DAXis(ESCALADO_FIG + 0.2f);
    }
    glutSwapBuffers();
}

void idle()
{
    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();
}

void ligth()
{
    glLightfv(GL_LIGHT0, GL_POSITION, posl1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spct);
}

void manageKeyBoardInput(unsigned char key, int x, int y)
{
    // Avoid unused warning
    x = x;
    y = y;

    // const float inc = 0.1f;

    switch (key)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        fig = key;
        break;
    case 27: // 'ESC'
        displayAxis = !displayAxis;
        break;
    case 'w':
        displayWired = !displayWired;
        break;
    case 'p':
        displayPlane = !displayPlane;
        break;
    default:
        break;
    }
}

void extraKeyBoardInput(int key, int x, int y)
{
    key = key;
    x = x;
    y = y;
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    // Inicializamos la librería GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // Creamos la nueva ventana
    glutCreateWindow("Etapa 5");
    glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST | GL_LIGHTING | GL_COLOR_MATERIAL);

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(manageKeyBoardInput);
    glutSpecialFunc(extraKeyBoardInput);
    glutIdleFunc(idle);
    ligth();

    glClearColor(BG_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}
