#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../templates/base.h"

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
const float SQR_SIZE = 0.2f;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes.

// Función que controla la proporción al cambiar el tamaño
void reshape(int width, int height)
{
    const float ar_origin = (float)W_WIDTH / (float)W_HEIGHT;
    const float ar_new = (float)width / (float)height;

    float scale_w = (float)width / (float)W_WIDTH;
    float scale_h = (float)height / (float)W_HEIGHT;
    if (ar_new > ar_origin)
    {
        scale_w = scale_h;
    }
    else
    {
        scale_h = scale_w;
    }

    float margin_x = (width - W_WIDTH * scale_w) / 2;
    float margin_y = (height - W_HEIGHT * scale_h) / 2;

    glViewport(margin_x, margin_y, W_WIDTH * scale_w, W_HEIGHT * scale_h);
}

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
    glColor4f(LIGHT);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(RED);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor4f(GREEN);
    glVertex3f(-0.5f, 0.866f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(LIGHT);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(RED);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor4f(BLUE);
    glVertex3f(-0.5f, -0.866f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(LIGHT);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor4f(GREEN);
    glVertex3f(-0.5f, 0.866f, 0.0f);
    glColor4f(BLUE);
    glVertex3f(-0.5f, -0.866f, 0.0f);
    glEnd();

    // Cuadrado
    glBegin(GL_POLYGON);
    glColor4f(DARK);
    glVertex2f(-SQR_SIZE, SQR_SIZE);
    glVertex2f(SQR_SIZE, SQR_SIZE);
    glVertex2f(SQR_SIZE, -SQR_SIZE);
    glVertex2f(-SQR_SIZE, -SQR_SIZE);
    glEnd();

    glPopMatrix();

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
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    // El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
    glClearColor(BG_COLOR);

    // Comienza la ejecuci�n del core de GLUT
    glutMainLoop();
    return 0;
}