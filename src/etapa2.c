#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define BG_COLOR 0.0f, 0.0f, 0.0f, 0.0f // NEGRO

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes.

// Funci�n que visualiza la escena OpenGL
void display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    // Rotamos las proximas primitivas
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
    // Creamos a continuaci�n dibujamos los tres poligonos
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.866f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.866f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, 0.866f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.866f, 0.0f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();

    glFlush();
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void idle(void)
{
    // Incrementamos el �ngulo
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

// Funci�n principal
int main(int argc, char **argv)
{
    // Inicializamos la librer�a GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Creamos la nueva ventana
    glutCreateWindow("Mi primera Ventana");

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
    glClearColor(BG_COLOR);
    glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

    // Comienza la ejecuci�n del core de GLUT
    glutMainLoop();
    return 0;
}