#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../templates/base.h"

const int W_WIDTH = 600; // Tama�o incial de la ventana
const int W_HEIGHT = 600;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes.

// Funci�n que visualiza la escena OpenGL
void display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // set the modelview matrix
    glLoadIdentity();           // load the identity matrix

    glEnable(GL_LINE_SMOOTH); // enable anti-aliasing

    const float TAM_ESC = 1.0;

    // ---- CUADRANTE ARRIBA - IZQ -------
    glTranslatef(0.2f, 0.2f, 0.2f); // Translación
    glBegin(GL_QUADS);
    glColor4f(LIGHT);                              // blanco
    glVertex2f(-0.75f * TAM_ESC, 0.25f * TAM_ESC); // arriba-izquierda
    glVertex2f(-0.75f * TAM_ESC, 0.75f * TAM_ESC); // abajo-izquierda
    glVertex2f(-0.25f * TAM_ESC, 0.75f * TAM_ESC); // abajo-derecha
    glVertex2f(-0.25f * TAM_ESC, 0.25f * TAM_ESC); // arriba-derecha
    glEnd();
    glLoadIdentity();

    // ---- CUADRANTE ABAJO - IZQ -------
    glRotatef(45.0f, -0.5f, -0.5f, 0.0f); // Rotación
    glBegin(GL_QUADS);
    glColor4f(LIGHT);                               // blanco
    glVertex2f(-0.75f * TAM_ESC, -0.25f * TAM_ESC); // arriba-izquierda
    glVertex2f(-0.75f * TAM_ESC, -0.75f * TAM_ESC); // abajo-izquierda
    glVertex2f(-0.25f * TAM_ESC, -0.75f * TAM_ESC); // abajo-derecha
    glVertex2f(-0.25f * TAM_ESC, -0.25f * TAM_ESC); // arriba-derecha
    glEnd();
    glLoadIdentity();

    // ---- CUADRANTE ABAJO - DER-------
    glScalef(1.5f, 1.5f, 0.0f); // Escalado
    glBegin(GL_QUADS);
    glColor4f(LIGHT);                              // blanco
    glVertex2f(0.75f * TAM_ESC, -0.25f * TAM_ESC); // arriba-izquierda
    glVertex2f(0.75f * TAM_ESC, -0.75f * TAM_ESC); // abajo-izquierda
    glVertex2f(0.25f * TAM_ESC, -0.75f * TAM_ESC); // abajo-derecha
    glVertex2f(0.25f * TAM_ESC, -0.25f * TAM_ESC); // arriba-derecha
    glEnd();
    glLoadIdentity();

    // ---- CUADRANTE ARRIBA - DER-------
    GLfloat m[4 * 4] = {
        1.0f, -0.25f, 0.3f, 0.0f,
        0.7f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.3f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    glMultMatrixf(m);
    glBegin(GL_QUADS);
    glColor4f(LIGHT);                             // blanco
    glVertex2f(0.75f * TAM_ESC, 0.25f * TAM_ESC); // arriba-izquierda
    glVertex2f(0.75f * TAM_ESC, 0.75f * TAM_ESC); // abajo-izquierda
    glVertex2f(0.25f * TAM_ESC, 0.75f * TAM_ESC); // abajo-derecha
    glVertex2f(0.25f * TAM_ESC, 0.25f * TAM_ESC); // arriba-derecha
    glEnd();
    glLoadIdentity();

    // Ejes
    glColor4f(PURE_WHITE);
    // Eje x
    glBegin(GL_LINES);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();

    // Eje y
    glBegin(GL_LINES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, -1.0f);
    glEnd();

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
    glutCreateWindow("Etapa 2");

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
    glClearColor(BG_COLOR);

    // Comienza la ejecuci�n del core de GLUT
    glutMainLoop();
    return 0;
}