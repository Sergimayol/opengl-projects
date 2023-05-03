#include "./base.h"

const int W_WIDTH = 600; // Tamaño incial de la ventana
const int W_HEIGHT = 600;

void display()
{
	// Scene code here

	glutSwapBuffers();
}

void idle()
{
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
	glutCreateWindow("CHANGE ME");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glClearColor(BG_COLOR);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}
