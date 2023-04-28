#include "../templates/base.h"

const int W_WIDTH = 600; // Tamaño incial de la ventana
const int W_HEIGHT = 600;
GLfloat fAngulo;

void drawCube()
{
    glPushMatrix();
    glLoadIdentity();
    glRotatef(fAngulo, 1.5f, 1.5f, 0.5f); // rotate the cube

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set the color of the cube
    glColor3f(1.0f, 0.0f, 0.0f); // red

    // draw the cube
    glutSolidCube(1.0f * 0.5f); // specify the size of the cube
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

    drawCube();
    draw3DAXis();

    glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void idle(void)
{
    // Incrementamos el ángulo
    fAngulo += 0.3f;
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
    glutIdleFunc(idle);

    glClearColor(BG_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}
