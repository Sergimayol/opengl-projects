#include "etapa4.h"

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
unsigned char fig = '1';

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2.0, 2.0, 2.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at position
              0.0, 1.0, 0.0); // Up vector

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

void manageKeyBoardInput(unsigned char key, int x, int y)
{
    // Avoid unused warning
    x = x;
    y = y;

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
    case 'p':
        displayPlane = !displayPlane;
        break;
    default:
        break;
    }
}

void reshapeFrustum(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
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
    glutCreateWindow("Etapa 4");
    glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST);

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFrustum);
    glutKeyboardFunc(manageKeyBoardInput);
    glutIdleFunc(idle);

    glClearColor(BG_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}
