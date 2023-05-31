#include "etapa4.h"
#include "camera.h"
#include "figures.h"

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
bool displayPlane = false;
bool displayAxis = true;
bool displayWired = true;
unsigned char fig = '1';
// The camera struct
Camera cam;
// Figure config
float rotationCoords[] = {0.0f, 1.0f, 0.0f};
struct Color3f figColor = {
	.r = 0.251,
	.g = 0.51f,
	.b = 0.427f};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float lookingAtX;
	float lookingAtY;
	float lookingAtZ;
	calcTargetPoint(&cam, &lookingAtX, &lookingAtY, &lookingAtZ);

	gluLookAt(cam.position.x, cam.position.y, cam.position.z,
			  lookingAtX, lookingAtY, lookingAtZ,
			  cam.up.x, cam.up.y, cam.up.z);

	switch (fig)
	{
	case '1':
		drawTeapot(0.5 * ESCALADO_FIG, 0, rotationCoords, displayWired, figColor);
		break;
	case '2':
		drawDonut(0.5 * ESCALADO_FIG, 20, 0, rotationCoords, displayWired, figColor);
		break;
	default:
		drawSphere(0.5 * ESCALADO_FIG, 20, 0, rotationCoords, displayWired, figColor);
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
	case 27: // 'ESC'
		displayAxis = !displayAxis;
		break;
	case 't':
		displayWired = !displayWired;
		break;
	case 'p':
		displayPlane = !displayPlane;
		break;
	case 'w': // Move camera forward
		moveCameraForward(&cam, inc);
		break;
	case 's': // Move camera backward
		moveCameraBackward(&cam, inc);
		break;
	case 'a': // Strafe camera left
		starfeCameraLeft(&cam, inc);
		break;
	case 'd': // Strafe camera right
		starfeCameraRight(&cam, inc);
		break;
	case 'q': // Move camera up
		moveCameraUp(&cam, inc);
		break;
	case 'e': // Move camera down
		moveCameraDown(&cam, inc);
		break;
	default:
		break;
	}

	printCamera(&cam);
	glutPostRedisplay();
}

void extraKeyBoardInput(int key, int x, int y)
{
	// Avoid unused warning
	x = x;
	y = y;

	const float inc = 0.1f;

	switch (key)
	{
	case GLUT_KEY_LEFT: // Rotate camera left
		rotateCameraLeft(&cam, inc);
		break;
	case GLUT_KEY_RIGHT: // Rotate camera right
		rotateCameraRight(&cam, inc);
		break;
	case GLUT_KEY_UP: // Rotate camera up
		rotateCameraUp(&cam, inc);
		break;
	case GLUT_KEY_DOWN: // Rotate camera down
		rotateCameraDown(&cam, inc);
		break;
	default:
		break;
	}

	printCamera(&cam);
	glutPostRedisplay();
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

	initCamera(&cam);

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
