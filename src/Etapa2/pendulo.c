#include "../templates/base.h"

const int W_WIDTH = 600; // Tamaño incial de la ventana
const int W_HEIGHT = 600;
GLfloat fAnguloInt; // Variable que indica el ángulo de rotación de los ejes.
GLfloat fAnguloExt; // Variable que indica el ángulo de rotación de los ejes.

// Función que visualiza la escena OpenGL
void display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // set the modelview matrix
    glEnable(GL_LINE_SMOOTH);   // enable anti-aliasing

    const float ESCALADO = 0.5f;
    glPushMatrix();
    // Pendulo 1
    glRotatef(fAnguloInt, 0.0f, 0.0f, 1.0f);
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f * ESCALADO, 0.5f);
    glEnd();

    glPushMatrix();
    // Pendulo 2
    glTranslatef(1.0f * ESCALADO, 0.5f, 0.0f);
    glRotatef(fAnguloExt, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f * ESCALADO, -0.5f, 0.0f);
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex2f(1.0f * ESCALADO, 0.5f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // ------ Ejes X - Y ------
    glPushMatrix();
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
    glPopMatrix();
    // ------------------------

    glutSwapBuffers();

    glFlush();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void idle(void)
{
    // Incrementamos el ángulo
    fAnguloInt += 0.1f;
    fAnguloExt += 0.3f;
    // Si es mayor que dos pi la decrementamos
    if (fAnguloInt > 360)
        fAnguloInt -= 360;

    if (fAnguloExt > 360)
        fAnguloExt -= 360;

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

// Función principal
int main(int argc, char **argv)
{
    // Inicializamos la librería GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Creamos la nueva ventana
    glutCreateWindow("Etapa 2 - Pendulo");

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // El color de fondo será el negro (RGBA, RGB + Alpha channel)
    glClearColor(BG_COLOR);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}