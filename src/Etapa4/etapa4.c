#include "etapa4.h"

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
unsigned char fig = '1';
// Rotation camera angle
float cameraAngle = 0.0f;
// Rotation camera radius
float cameraRadius = 5.0f;
// Rotation camera height
float cameraHeight = 2.0f;
// Eyte position
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
// Controla el modo en que se comporta la cámara
unsigned int mode = 0;
unsigned int TOTAL_MODES = 2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    eyeXDirection = upX + cameraRadius * sin(cameraAngle);
    eyeYDirection = upY + cameraHeight;
    eyeZDirection = upZ + cameraRadius * cos(cameraAngle);
    gluLookAt(eyeXDirection, eyeYDirection, eyeZDirection, // Eye position
              lookAtX, lookAtY, lookAtZ,                   // Look-at position
              upX, upY, upZ);                              // Up vector

    float rotationCoords[] = {0.0f, 1.0f, 0.0f};
    struct Color3f teapotColor;
    teapotColor.r = 1.0f;
    teapotColor.g = 0.0f;
    teapotColor.b = 0.0f;
    drawTeapot(0.5 * ESCALADO_FIG, 0, rotationCoords, true, teapotColor);

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
    case 'm':
        if (mode == TOTAL_MODES - 1)
        {
            mode = 0;
        }
        else
        {
            mode += 1;
        }
        break;
    default:
        break;
    }
}

void extraKeyBoardInput(int key, int x, int y)
{
    // Avoid unused warning
    x = x;
    y = y;

    const float inc = 0.1f;
    bool adjustCamAng = false;

    switch (key)
    {
    case GLUT_KEY_DOWN:
        if (mode == 0)
        {
            cameraRadius += inc;
            adjustCamAng = true;
        }
        break;
    case GLUT_KEY_UP:
        if (mode == 0)
        {
            cameraRadius -= inc;
            adjustCamAng = true;
        }
        break;
    case GLUT_KEY_LEFT:
        // Rotate camera around the object counterclockwise
        cameraAngle += 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        // Rotate camera around the object clockwise
        cameraAngle -= 0.1f;
        break;
    case GLUT_KEY_F1:
        eyeXDirection = 2.0;
        eyeYDirection = 2.0;
        eyeZDirection = 2.0;
        break;
    case GLUT_KEY_F2:
        eyeXDirection = 1.0;
        eyeYDirection = 3.2;
        eyeZDirection = 2.5;
        break;
    case GLUT_KEY_F3:
        eyeXDirection = 3.6;
        eyeYDirection = 1.3;
        eyeZDirection = 2.0;
        break;
    case GLUT_KEY_F4:
        eyeXDirection = 1.2;
        eyeYDirection = 1.5;
        eyeZDirection = 2.9;
        break;
    case GLUT_KEY_F5:
        eyeXDirection = 3.0;
        eyeYDirection = 2.2;
        eyeZDirection = 2.7;
        break;
    default:
        break;
    }
    if (adjustCamAng)
    {
        // Adjust camera height relative to the object's center
        cameraHeight = cameraRadius * sin(cameraAngle);
    }
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
    glutCreateWindow("Etapa 4");
    glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST);

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(manageKeyBoardInput);
    glutSpecialFunc(extraKeyBoardInput);
    glutIdleFunc(idle);

    glClearColor(BG_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}
