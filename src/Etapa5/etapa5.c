#include "etapa5.h"
#include <stdio.h>

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
bool displayWired = true;
unsigned char fig = '1';

// Eye position
float eyeXDirection = 3.0f;
float eyeYDirection = 3.0f;
float eyeZDirection = 3.0f;
// Look-at position
float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;
// Up vector
float upX = 0.0f;
float upY = 1.0f;
float upZ = 0.0f;
// Set light properties
GLfloat light_position[] = {0.0f, 2.0f, 0.0f, 0.0f}; // Light position
GLfloat light_position1[] = {2.0f, 0.0f, 0.0f, 0.0f};
GLfloat light_position2[] = {0.0f, 0.0f, 2.0f, 0.0f};
// Set material properties
float fAngulo = 0.0f;

float rotationCoords[] = {0.0f, 1.0f, 0.0f};
struct Color3f figColor = {0.251f, 0.51f, 0.427f};

bool isFlat = false;
bool light1On = false;
bool light2On = false;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeXDirection, eyeYDirection, eyeZDirection, // Eye position
			  lookAtX, lookAtY, lookAtZ,				   // Look-at position
			  upX, upY, upZ);							   // Up vector

	switch (fig)
	{
	case '1':
		drawTeapot(0.5 * ESCALADO_FIG, fAngulo, rotationCoords, displayWired, figColor);
		break;
	case '2':
		drawDonut(0.5 * ESCALADO_FIG, 20, fAngulo, rotationCoords, displayWired, figColor);
		break;
	default:
		break;
	}

	if (isFlat)
	{
		glShadeModel(GL_FLAT);
	}
	else
	{
		glShadeModel(GL_SMOOTH);
	}

	if (light1On)
	{
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}

	if (light2On)
	{
		glEnable(GL_LIGHT2);
	}
	else
	{
		glDisable(GL_LIGHT2);
	}

	glDisable(GL_LIGHTING);
	if (light1On)
	{
		glPushMatrix();
		glTranslatef(light_position1[0], light_position1[1], light_position1[2]);
		drawSphere(0.1 * ESCALADO_FIG, 20, 20, rotationCoords, false, (struct Color3f){0.89803921569f, 0.78431372549f, 0.56470588235f});
		glPopMatrix();
	}
	if (light2On)
	{
		glPushMatrix();
		glTranslatef(light_position2[0], light_position2[1], light_position2[2]);
		drawSphere(0.1 * ESCALADO_FIG, 20, 20, rotationCoords, false, (struct Color3f){0.65098039216f, 0.81960784314f, 0.53725490196f});
		glPopMatrix();
	}
	if (displayPlane)
	{
		drawPlanes(ESCALADO_FIG);
	}

	if (displayAxis)
	{
		draw3DAXis(ESCALADO_FIG + 0.2f);
	}

	glPushMatrix();
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	drawSphere(0.1 * ESCALADO_FIG, 20, 20, rotationCoords, false, (struct Color3f){1.0f, 1.0f, 1.0f});
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

void init_lights()
{
	const GLfloat mat_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
	const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	const GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	const GLfloat light_ambient[] = {BG_COLOR}; // Ambient light color

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat[]){LIGHT});
	glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat[]){PURE_WHITE});
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat[]){YELLOW});
	glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat[]){YELLOW});
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat[]){BLUE});
	glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat[]){BLUE});
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
}

void idle()
{
	// Incrementamos el ángulo
	fAngulo += 0.1f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

void manageKeyBoardInput(unsigned char key, int x, int y)
{
	// Avoid unused warning
	x = x;
	y = y;

	const float inc = 0.3f;

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
	case 'w':
		displayWired = !displayWired;
		break;
	case 'p':
		displayPlane = !displayPlane;
		break;
	case 'a':
		// pos x
		light_position[0] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 'z':
		// pos x
		light_position[0] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 's':
		// pos y
		light_position[1] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 'x':
		// pos y
		light_position[1] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 'd':
		// pos z
		light_position[2] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 'c':
		// pos z
		light_position[2] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;
	case 32: // Space
		// Change light mode
		isFlat = !isFlat;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void extraKeyBoardInput(int key, int x, int y)
{
	key = key;
	x = x;
	y = y;

	switch (key)
	{
	case GLUT_KEY_F1:
		light1On = !light1On;
		break;
	case GLUT_KEY_F2:
		light2On = !light2On;
		break;
	default:
		break;
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
	glutCreateWindow("Etapa 5");
	glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST | GL_COLOR_MATERIAL);

	init_lights();

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
