#include "base.h"

void draw3DAXis(const float ESCALADO)
{
    glPushMatrix();
    glBegin(GL_LINES);
    // X
    glColor4f(YELLOW);
    glVertex3f(-1.0f * ESCALADO, 0.0f, 0.0f);
    glVertex3f(1.0f * ESCALADO, 0.0f, 0.0f);
    // Y
    glColor4f(GREEN);
    glVertex3f(0.0f, -1.0f * ESCALADO, 0.0f);
    glVertex3f(0.0f, 1.0f * ESCALADO, 0.0f);
    glEnd();

    // Z
    // glRotatef(180.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glColor4f(BLUE);
    glVertex3f(0.0f, 0.0f, -1.0f * ESCALADO);
    glVertex3f(0.0f, 0.0f, 1.0f * ESCALADO);
    glEnd();
    glPopMatrix();
}

void drawPlanes(const float ESCALADO)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    // X - Y
    glColor4f(YELLOW_ALPHA);
    glVertex3f(1.0f * ESCALADO, 1.0f * ESCALADO, 0.0f);
    glVertex3f(-1.0f * ESCALADO, 1.0f * ESCALADO, 0.0f);
    glVertex3f(-1.0f * ESCALADO, -1.0f * ESCALADO, 0.0f);
    glVertex3f(1.0f * ESCALADO, -1.0f * ESCALADO, 0.0f);
    glEnd();

    // X - Z
    glBegin(GL_QUADS);
    glColor4f(GREEN_ALPHA);
    glVertex3f(1.0f * ESCALADO, 0.0f, 1.0f * ESCALADO);
    glVertex3f(-1.0f * ESCALADO, 0.0f, 1.0f * ESCALADO);
    glVertex3f(-1.0f * ESCALADO, 0.0f, -1.0f * ESCALADO);
    glVertex3f(1.0f * ESCALADO, 0.0f, -1.0f * ESCALADO);
    glEnd();

    // Y - Z
    glBegin(GL_QUADS);
    glColor4f(BLUE_ALPHA);
    glVertex3f(0.0f, 1.0f * ESCALADO, 1.0f * ESCALADO);
    glVertex3f(0.0f, -1.0f * ESCALADO, 1.0f * ESCALADO);
    glVertex3f(0.0f, -1.0f * ESCALADO, -1.0f * ESCALADO);
    glVertex3f(0.0f, 1.0f * ESCALADO, -1.0f * ESCALADO);
    glEnd();
    glPopMatrix();
}
