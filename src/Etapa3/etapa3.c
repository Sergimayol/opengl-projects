#include "../templates/base.h"
#include <stdbool.h>

const int W_WIDTH = 600; // Tamaño incial de la ventana
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 0.5f;
GLfloat fAngulo;
unsigned char fig = 'c';
bool displayAxis = true;
bool displayWithWire = true;

void drawDonut()
{
    glPushMatrix();
    glLoadIdentity();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);   // Rotate the object around the x-axis
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);   // Rotate the object around the y-axis
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f); // rotate the cube

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set the color of the cube
    glColor3f(1.0f, 0.0f, 0.0f); // red

    const int NUM_OF_SLICES = 20;
    if (displayWithWire)
    {
        glutWireTorus(1.0 * ESCALADO_FIG, 1.0 * ESCALADO_FIG, NUM_OF_SLICES, NUM_OF_SLICES); // Render a cone with base radius 1.0 and height 2.0
    }
    else
    {
        glutSolidTorus(1.0 * ESCALADO_FIG, 1.0 * ESCALADO_FIG, NUM_OF_SLICES, NUM_OF_SLICES); // Render a cone with base radius 1.0 and height 2.0
    }

    glEnd();
    glPopMatrix();
}

void drawTriangle()
{
    glPushMatrix();
    glLoadIdentity();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);   // Rotate the object around the x-axis
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);   // Rotate the object around the y-axis
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f); // rotate the cube

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set the color of the cube
    glColor3f(1.0f, 0.0f, 0.0f); // red

    const int NUM_OF_SLICES = 20;
    if (displayWithWire)
    {
        glutWireCone(1.0 * ESCALADO_FIG, 1.0 * ESCALADO_FIG, NUM_OF_SLICES, NUM_OF_SLICES); // Render a cone with base radius 1.0 and height 2.0
    }
    else
    {
        glutSolidCone(1.0 * ESCALADO_FIG, 1.0 * ESCALADO_FIG, NUM_OF_SLICES, NUM_OF_SLICES); // Render a cone with base radius 1.0 and height 2.0
    }

    glEnd();
    glPopMatrix();
}

void drawCube()
{
    glPushMatrix();
    glLoadIdentity();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);   // Rotate the object around the x-axis
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);  // Rotate the object around the y-axis
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f); // rotate the cube

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set the color of the cube
    glColor3f(1.0f, 0.0f, 0.0f); // red

    // draw the cube
    if (displayWithWire)
    {
        glutWireCube(1.0f * ESCALADO_FIG); // specify the size of the cube
    }
    else
    {
        glutSolidCube(1.0f * ESCALADO_FIG); // specify the size of the cube
    }
    glEnd();
    glPopMatrix();
}

void draw3DAXis()
{
    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_LINES);
    // X
    glColor4f(YELLOW);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    // Y
    glColor4f(GREEN);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Z
    glRotatef(180.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glColor4f(BLUE);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH | GL_DEPTH);
    glMatrixMode(GL_MODELVIEW);

    switch (fig)
    {
    case 'c':
        drawCube();
        break;
    case 't':
        drawTriangle();
        break;
    case 'd':
        drawDonut();
        break;
    default:
        break;
    }
    if (displayAxis)
    {
        draw3DAXis();
    }

    glutSwapBuffers();
}

void manageKeyBoardInput(unsigned char key, int x, int y)
{
    // Avoid unused warning
    x = x;
    y = y;

    switch (key)
    {
    case 'c':
    case 't':
    case 'd':
        fig = key;
        break;
    case 'w':
        displayWithWire = !displayWithWire;
        break;
    case 27: // 'ESC'
        displayAxis = !displayAxis;
        break;
    default:
        break;
    }
}

// Función que se ejecuta cuando el sistema no esta ocupado
void idle(void)
{
    // Incrementamos el ángulo
    fAngulo += 0.1f;
    // Si es mayor que dos pi la decrementamos
    if (fAngulo > 360)
        fAngulo -= 360;
    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();
}

void reshape(GLsizei width, GLsizei height)
{
    // Calcular el aspect ratio de la nueva ventana
    if (height == 0)
    {
        height = 1; // Para evitar dividir por cero
    }
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    // Hacer que el viewport cubra la nueva ventana
    glViewport(0, 0, width, height);
    // Hacer que el aspect ratio del área de dibujado sea igual al del viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
        glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
    }
    else
    {
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    // Inicializamos la librería GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Creamos la nueva ventana
    glutCreateWindow("Etapa 3");

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(manageKeyBoardInput);
    glutIdleFunc(idle);

    glClearColor(BG_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}
