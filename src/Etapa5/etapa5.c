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
GLfloat light_positions[3][4] = {
	{0.0f, 2.0f, 0.0f, 0.0f},
	{2.0f, 0.0f, 0.0f, 0.0f},
	{-2.0f, 0.0f, 0.0f, 0.0f}};
struct Color3f light_colors[3] = {
	{1.0f, 1.0f, 1.0f},
	{0.89803921569f, 0.78431372549f, 0.56470588235f},
	{0.65098039216f, 0.81960784314f, 0.53725490196f}};
bool light_status[] = {true, false, false, false};

float fAngulo = 0.0f;
float rotationCoords[] = {0.0f, 1.0f, 0.0f};
struct Color3f figColor = {0.251f, 0.51f, 0.427f};

bool isFlat = false;

void draw_figure(unsigned char index)
{

	switch (index)
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
}
void manage_lights()
{
	const int arr_len = sizeof(light_status) / sizeof(light_status[0]);
	for (int i = 0; i < arr_len; i++)
	{
		if (light_status[i])
		{
			glEnable(GL_LIGHT0 + i);

			glDisable(GL_LIGHTING);
			glPushMatrix();
			glTranslatef(light_positions[i][0], light_positions[i][1], light_positions[i][2]);
			drawSphere(0.1 * ESCALADO_FIG, 20, 20, rotationCoords, false, light_colors[i]);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHT0 + i);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeXDirection, eyeYDirection, eyeZDirection, // Eye position
			  lookAtX, lookAtY, lookAtZ,				   // Look-at position
			  upX, upY, upZ);							   // Up vector

	manage_lights();
	draw_figure(fig);
	glShadeModel(isFlat ? GL_FLAT : GL_SMOOTH);

	glDisable(GL_LIGHTING);
	displayPlane ? drawPlanes(ESCALADO_FIG) : NULL;
	displayAxis ? draw3DAXis(ESCALADO_FIG + 0.2f) : NULL;
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

void init_lights()
{
	const GLfloat mat_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat mat_color[] = {LIGHT}; // Ambient light color
	const GLfloat mat_shininess[] = {15.0f};
	const GLfloat light_ambient[] = {BG_COLOR}; // Ambient light color

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	// Enable lighting
	glEnable(GL_LIGHTING);

	const int arr_len = sizeof(light_status) / sizeof(light_status[0]);
	for (int i = 0; i < arr_len; i++)
	{
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, (GLfloat[]){light_colors[i].r, light_colors[i].g, light_colors[i].b});
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, (GLfloat[]){light_colors[i].r, light_colors[i].g, light_colors[i].b});
		glLightfv(GL_LIGHT0 + i, GL_POSITION, light_positions[i]);
	}
	glEnable(GL_LIGHT0);
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
		light_positions[0][0] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
		break;
	case 'z':
		// pos x
		light_positions[0][0] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
		break;
	case 's':
		// pos y
		light_positions[0][1] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
		break;
	case 'x':
		// pos y
		light_positions[0][1] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
		break;
	case 'd':
		// pos z
		light_positions[0][2] += inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
		break;
	case 'c':
		// pos z
		light_positions[0][2] -= inc;
		glLightfv(GL_LIGHT0, GL_POSITION, light_positions[0]);
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
		light_status[0] = !light_status[0];
		break;
	case GLUT_KEY_F2:
		light_status[1] = !light_status[1];
		break;
	case GLUT_KEY_F3:
		light_status[2] = !light_status[2];
		break;
	case GLUT_KEY_F4:
		light_status[3] = !light_status[3];
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
