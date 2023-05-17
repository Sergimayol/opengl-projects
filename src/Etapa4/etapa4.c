#include "etapa4.h"

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
bool displayWired = true;
unsigned char fig = '1';
// Rotation camera angle
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
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
// The camera will rotate from the center object of the scene
const unsigned int ROTATE_FROM_CENTER = 0;
// The camera will rotate from his own axis
const unsigned int ROTATE_FROM_OWN = 1;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    eyeXDirection = upX + cameraRadius * sin(cameraAngleX) * cos(cameraAngleY);
    eyeYDirection = upY + cameraHeight;
    eyeZDirection = upZ + cameraRadius * cos(cameraAngleX) * cos(cameraAngleY);

    if (mode == ROTATE_FROM_CENTER)
    {

        eyeYDirection = upY + cameraRadius * sin(cameraAngleY);
    }

    gluLookAt(eyeXDirection, eyeYDirection, eyeZDirection, // Eye position
              lookAtX, lookAtY, lookAtZ,                   // Look-at position
              upX, upY, upZ);                              // Up vector
                                                           // Up vector

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

void manageKeyBoardInput(unsigned char key, int x, int y)
{
    // Avoid unused warning
    x = x;
    y = y;

    const float inc = 0.1f;

    switch (key)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        fig = key;
        break;
    case 'j':
        cameraAngleY -= inc;
        break;
    case 'k':
        cameraAngleY += inc;
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
        if (mode == ROTATE_FROM_CENTER)
        {
            cameraRadius += inc;
            adjustCamAng = true;
        }
        else if (mode == ROTATE_FROM_OWN)
        {
            lookAtY -= inc;
        }
        break;
    case GLUT_KEY_UP:
        if (mode == ROTATE_FROM_CENTER)
        {
            cameraRadius -= inc;
            adjustCamAng = true;
        }
        else if (mode == ROTATE_FROM_OWN)
        {
            lookAtY += inc;
        }
        break;
    case GLUT_KEY_LEFT:
        if (mode == ROTATE_FROM_CENTER)
        {
            // Rotate camera around the object counterclockwise
            cameraAngleX -= 0.1f;
        }
        else if (mode == ROTATE_FROM_OWN)
        {
            lookAtX -= inc;
            lookAtZ -= inc;
            adjustCamAng = true;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (mode == ROTATE_FROM_CENTER)
        {
            // Rotate camera around the object clockwise
            cameraAngleX += 0.1f;
        }
        else if (mode == ROTATE_FROM_OWN)
        {
            lookAtX += inc;
            lookAtZ += inc;
            adjustCamAng = true;
        }
        break;
    case GLUT_KEY_F1:
        cameraAngleX = 3.2;
        cameraRadius = 3.0;
        cameraHeight = 4.2;
        break;
    case GLUT_KEY_F2:
        cameraAngleX = 7.5;
        cameraRadius = 3.0;
        cameraHeight = 5.2;
        break;
    case GLUT_KEY_F3:
        cameraAngleX = 4.6;
        cameraRadius = 7.0;
        cameraHeight = 2.5;
        break;
    case GLUT_KEY_F4:
        cameraAngleX = 1.9;
        cameraRadius = 3.5;
        cameraHeight = 4.0;
        break;
    case GLUT_KEY_F5:
        cameraAngleX = 6.5;
        cameraRadius = 3.0;
        cameraHeight = 4.2;
        break;
    case GLUT_KEY_F6:
        cameraAngleX = 2.9;
        cameraRadius = 2.5;
        cameraHeight = 1.2;
        break;
    case GLUT_KEY_F7:
        cameraHeight = 0;
        lookAtY = 0.0;
        break;
    default:
        break;
    }
    if (adjustCamAng)
    {
        // Adjust camera height relative to the object's center
        cameraHeight = cameraRadius * sin(cameraAngleX);
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
