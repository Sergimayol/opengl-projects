#include "base.h"

void drawTeapot(const GLdouble size, float rotationAngle,
				float rotationCoords[], bool displayWired,
				float figColor[])
{
	glPushMatrix();
	glRotatef(rotationAngle, rotationCoords[0], rotationCoords[1], rotationCoords[2]);
	glColor4fv(figColor);
	displayWired ? glutWireTeapot(size) : glutSolidTeapot(size);
	glPopMatrix();
}
void drawDonut(const GLdouble size, const int slices,
			   float rotationAngle, float rotationCoords[],
			   bool displayWired, float figColor[])
{
	glPushMatrix();
	glRotatef(rotationAngle, rotationCoords[0], rotationCoords[1], rotationCoords[2]);
	glColor4fv(figColor);
	displayWired ? glutWireTorus(size, size, slices, slices) : glutSolidTorus(size, size, slices, slices);
	glPopMatrix();
}

void drawSphere(const GLdouble size, const int slices, bool displayWired, float figColor[])
{
	glPushMatrix();
	glColor4fv(figColor);
	displayWired ? glutWireSphere(size, slices, slices) : glutSolidSphere(size, slices, slices);
	glPopMatrix();
}