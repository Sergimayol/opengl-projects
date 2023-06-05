#include "etapa6.h"
#include "base.h"
#include "map.h"
#include "object.h"
#include "texture.h"
#include <GL/gl.h>
#include <stdio.h>

#define ON true
#define OFF false

const int W_HEIGHT = 640;
const int W_WIDTH = 940;
const float ESCALADO_FIG = 1.5f;
const float inc = 0.1f;
const float scaleFactor = 0.05;

float fogDensity = 0.02f;
float fAngulo = 0.0f;
float fAnguloPag1 = 0.0f;
float fAnguloPag2 = 1.0f;
float bAngulo = 0.0f;

bool displayPlane = false;
bool displayAxis = false;
bool isFlat = true;

Room room;
TextureIdCounter textCounter;
Texture roomText;
Texture bookPageText;

Camera cam = {
	.position = {0.0f, 1.6f, 3.8f},
	.lookingAt = {0.0f, 0.0f, 4.0f},
	.up = {0.0f, 1.0f, 0.0f},
	.yaw = 0.0f,
	.pitch = -0.4f};

Light lights[] = {{0, ON, {BG_COLOR}, {PURE_WHITE}, {PURE_WHITE}, {0.0f, 2.0f, 0.0f, 0.0f}},
				  {1, OFF, {BG_COLOR}, {RED}, {RED}, {-1.6f, 0.45f, 0.8f, 0.0f}},
				  {2, OFF, {BG_COLOR}, {BLUE}, {BLUE}, {-0.7f, 0.45f, 1.4f, 0.0f}},
				  {3, OFF, {BG_COLOR}, {GREEN}, {GREEN}, {1.2f, 0.45f, 1.6f, 0.0f}}};

Object objects[] = {
	{.scene = NULL,
	 .mesh = NULL,
	 .material = NULL,
	 .objPath = "./src/Etapa6/objetos/book/book.obj"},
	{.scene = NULL,
	 .mesh = NULL,
	 .material = NULL,
	 .objPath = "./src/Etapa6/objetos/rat.obj"},
	{.scene = NULL,
	 .mesh = NULL,
	 .material = NULL,
	 .objPath = "./src/Etapa6/objetos/candle.obj"}};

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
			drawSphere(0.04 * ESCALADO_FIG, 20, false, lights[i].specular);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
		else
		{
			off(&lights[i]);
		}
	}
}

float mapBounce(float value, float outputMin, float outputMax)
{
	return (value + 1.0f) * 0.5f * (outputMax - outputMin) + outputMin;
}

void draw_page()
{
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bookPageText.textureId);
	glBegin(GL_QUADS);
	glColor4f(PURE_WHITE);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.8f);
    glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.8f);
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, -0.5f, -0.8f);
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, -0.8f);
	glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(isFlat ? GL_FLAT : GL_SMOOTH);
	glLoadIdentity();

	updateCamera(&cam);

	glFogf(GL_FOG_DENSITY, fogDensity); // Set fog density

	glPushMatrix();
	glTranslatef(0.0f, room.height / 2, 0.0f);
	draw_room(&room);
	glPopMatrix();

	glPushMatrix();
	glRotatef(fAngulo, 0.0f, 1.0f, 0.0f);
	// Página 1
	glPushMatrix();
	glTranslatef(0.0f, mapBounce(sin(bAngulo), 0.2f, 0.8f) + 0.5f, 0.0f);
	glRotatef(fAnguloPag1, 0.0f, 0.0f, 1.0f);
	draw_page();
	glPopMatrix();
	// Página 2
	glPushMatrix();
	glTranslatef(0.0f, mapBounce(sin(bAngulo), 0.2f, 0.8f) + 0.5f, 0.0f);
	glRotatef(fAnguloPag2, 0.0f, 0.0f, 1.0f);
	draw_page();
	glPopMatrix();
	glTranslatef(0.48f, mapBounce(sin(bAngulo), 0.2f, 0.8f), 0.15f);
	draw_object(&objects[0], true, true);

	glPopMatrix();

	glColor4f(YELLOW);
	// 🐀 Town
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glScalef(scaleFactor * 0.25f, scaleFactor * 0.25f, scaleFactor * 0.25f);
	glRotatef(fAngulo * 13, 0.0f, 1.0f, 0.0f);
	draw_object(&objects[1], true, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, -5.0f);
	glScalef(scaleFactor * 0.25f, scaleFactor * 0.25f, scaleFactor * 0.25f);
	glRotatef(fAngulo * 13, 0.0f, 1.0f, 0.0f);
	draw_object(&objects[1], true, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f, 0.0f, -5.0f);
	glScalef(scaleFactor * 0.25f, scaleFactor * 0.25f, scaleFactor * 0.25f);
	glRotatef(fAngulo * 13, 0.0f, 1.0f, 0.0f);
	draw_object(&objects[1], true, true);
	glPopMatrix();

	glColor4f(BLUE);
	// Candle Town
	glPushMatrix();
	glTranslatef(lights[1].position[0], 0.0f, lights[1].position[2]);
	draw_object(&objects[2], true, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lights[2].position[0], 0.0f, lights[2].position[2]);
	draw_object(&objects[2], true, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lights[3].position[0], 0.0f, lights[3].position[2]);
	draw_object(&objects[2], true, true);
	glPopMatrix();

//	manage_lights();
	glShadeModel(isFlat ? GL_FLAT : GL_SMOOTH);

//	glDisable(GL_LIGHTING);
	displayPlane ? drawPlanes(ESCALADO_FIG) : NULL;
	displayAxis ? draw3DAXis(ESCALADO_FIG + 0.2f) : NULL;
//	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

void initLights()
{
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

	fAnguloPag1 += 0.1f;
	if (fAnguloPag1 > 360)
		fAnguloPag1 -=360;

	fAnguloPag2 += 0.5f;
	if (fAnguloPag2 > 360)
		fAnguloPag2 -=360;

	// Incrementamos el ángulo
	bAngulo += 0.005f;
	// Si es mayor que dos pi la decrementamos
	if (bAngulo > 360)
		bAngulo -= 360;
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
		break;
	case 'x':
		fogDensity += 0.01f;
		break;
	case 'z':
		fogDensity -= 0.01f;
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
	gluPerspective(45.0, (double)width / (double)height, 1.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void initFog()
{
	glEnable(GL_DEPTH_TEST); // Enable depth testing
	glEnable(GL_FOG);		 // Enable fog

	glFogi(GL_FOG_MODE, GL_EXP);					  // Set fog mode to exponential
	glFogfv(GL_FOG_COLOR, (float[]){DARK_RAW, 1.0f}); // Set fog color
	glFogf(GL_FOG_DENSITY, fogDensity);				  // Set fog density
	glHint(GL_FOG_HINT, GL_NICEST);					  // Set fog hint
}

void initObjects()
{
	const int arr_len = sizeof(objects) / sizeof(objects[0]);
	for (int i = 0; i < arr_len; i++)
	{
		load_object(&objects[i]);
	}
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

	initFog();

//	initLights();
	init_texture_counter_id(&textCounter);

	init_texture(&roomText, &textCounter);
	load_texture(&roomText, "./src/Etapa6/objetos/wall/textures/wall1.jpg");
	init_room(&room, &roomText);

	init_texture(&bookPageText, &textCounter);
	load_texture(&bookPageText, "./src/Etapa6/objetos/book/textures/page.jpg");

	initObjects();

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
