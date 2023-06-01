#include "etapa6.h"

#define ON true
#define OFF false

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
const float ESCALADO_FIG = 1.5f;
const float inc = 0.3f;
bool displayPlane = false;
bool displayAxis = true;
const char *bookObj = "./src/Etapa6/objetos/book/book.obj";

Light lights[4] = {{0, ON, {BG_COLOR}, {PURE_WHITE}, {PURE_WHITE}, {0.0f, 2.0f, 0.0f, 0.0f}},
				   {1, OFF, {BG_COLOR}, {RED}, {RED}, {2.0f, 0.0f, 0.0f, 0.0f}},
				   {2, OFF, {BG_COLOR}, {BLUE}, {BLUE}, {0.0f, 2.0f, 0.0f, 0.0f}},
				   {3, OFF, {BG_COLOR}, {GREEN}, {GREEN}, {-2.0f, 0.0f, 0.0f, 0.0f}}};

float fAngulo = 0.0f;
float rotationCoords[] = {0.0f, 1.0f, 0.0f};
float figColor[] = {0.251f, 0.51f, 0.427f, 0.0f};

bool isFlat = false;

Camera cam;
Object book;

void manage_lights()
{
	const int arr_len = sizeof(lights) / sizeof(lights[0]);
	for (int i = 0; i < arr_len; i++)
	{
		if (lights[i].status)
		{
			on(&lights[i]);
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glTranslatef(lights[i].position[0], lights[i].position[1], lights[i].position[2]);
			drawSphere(0.1 * ESCALADO_FIG, 20, 20, rotationCoords, false, lights[i].specular);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
		else
		{
			off(&lights[i]);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCamera(&cam);

	glPushMatrix();
	glTranslatef(0.48f, 0.0f, 0.15f);
	draw_object(&book);
	glPopMatrix();

	manage_lights();
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

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	// Enable lighting
	glEnable(GL_LIGHTING);

	const int arr_len = sizeof(lights) / sizeof(lights[0]);
	for (int i = 0; i < arr_len; i++)
	{
		updateLight(&lights[i]);
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

	switch (key)
	{
	case 27: // 'ESC'
		displayAxis = !displayAxis;
		break;
	case 'p':
		displayPlane = !displayPlane;
		break;
	case 'h':
		// pos x
		lights[0].position[0] += inc;
		updatePosition(&lights[0]);
		break;
	case 'l':
		// pos x
		lights[0].position[0] -= inc;
		updatePosition(&lights[0]);
		break;
	case 'j':
		// pos y
		lights[0].position[1] += inc;
		updatePosition(&lights[0]);
		break;
	case 'k':
		// pos y
		lights[0].position[1] -= inc;
		updatePosition(&lights[0]);
		break;
	case 'o':
		// pos z
		lights[0].position[2] += inc;
		updatePosition(&lights[0]);
		break;
	case 'u':
		// pos z
		lights[0].position[2] -= inc;
		updatePosition(&lights[0]);
		break;
	case 32: // Space
		// Change light mode
		isFlat = !isFlat;
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
		lights[0].status = !lights[0].status;
		break;
	case GLUT_KEY_F2:
		lights[1].status = !lights[1].status;
		break;
	case GLUT_KEY_F3:
		lights[2].status = !lights[2].status;
		break;
	case GLUT_KEY_F4:
		lights[3].status = !lights[3].status;
		break;
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
	glutCreateWindow("Etapa 6");
	glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST | GL_COLOR_MATERIAL);

	initCamera(&cam);
	init_object(&book);
	load_object(&book, bookObj);
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
