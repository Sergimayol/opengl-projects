#include "base.h"

void drawTeapot(const GLdouble size, float rotationAngle,
				float rotationCoords[], bool displayWired,
				float figColor[])
{
	glPushMatrix();
	glRotatef(rotationAngle, rotationCoords[0], rotationCoords[1], rotationCoords[2]); // rotate the cube

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the color of the cube
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColor4fv(figColor);

	if (displayWired)
	{
		glutWireTeapot(size);
	}
	else
	{
		glutSolidTeapot(size);
	}

	glEnd();
	glPopMatrix();
}
void drawDonut(const GLdouble size, const int slices,
			   float rotationAngle, float rotationCoords[],
			   bool displayWired, float figColor[])
{
	glPushMatrix();
	glRotatef(rotationAngle, rotationCoords[0], rotationCoords[1], rotationCoords[2]); // rotate the cube

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the color of the cube
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColor4fv(figColor);

	if (displayWired)
	{
		glutWireTorus(size, size, slices, slices);
	}
	else
	{
		glutSolidTorus(size, size, slices, slices);
	}

	glEnd();
	glPopMatrix();
}

void drawSphere(const GLdouble size, const int slices,
				float rotationAngle, float rotationCoords[],
				bool displayWired, float figColor[])
{
	glPushMatrix();
	glRotatef(rotationAngle, rotationCoords[0], rotationCoords[1], rotationCoords[2]); // rotate the cube

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the color of the cube
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColor4fv(figColor);

	if (displayWired)
	{
		glutWireSphere(size, slices, slices);
	}
	else
	{
		glutSolidSphere(size, slices, slices);
	}

	glEnd();
	glPopMatrix();
}