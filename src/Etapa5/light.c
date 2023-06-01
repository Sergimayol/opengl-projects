#include <stdbool.h>
#include <string.h>
#include <GL/gl.h>

typedef struct
{
	int id;
	bool status;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];
} Light;

/**
 * @brief Updates the color properties of a Light source.
 *
 * @param light The Light source to update.
 */
void updateColor(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_DIFFUSE, light->diffuse);
	glLightfv(GL_LIGHT0 + light->id, GL_SPECULAR, light->specular);
}

/**
 * @brief Turns on a Light source.
 *
 * @param light The Light source to turn on.
 */
void on(Light *light)
{
	light->status = true;
	glEnable(GL_LIGHT0 + light->id);
}

/**
 * @brief Turns off a Light source.
 *
 * @param light The Light source to turn off.
 */
void off(Light *light)
{
	light->status = false;
	glDisable(GL_LIGHT0 + light->id);
}

/**
 * @brief Toggles a Light source.
 *
 * @param light The Light source to toggle.
 */
void toggle(Light *light)
{
	light->status = !light->status;
	light->status ? glEnable(GL_LIGHT0 + light->id) : glDisable(GL_LIGHT0 + light->id);
}

/**
 * @brief Updates the position of a Light source.
 *
 * @param light    The Light source to update.
 */
void updatePosition(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_POSITION, light->position);
}

/**
 * @brief Updates the ambient color of a Light source.
 *
 * @param light   The Light source to update.
 */
void updateAmbient(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_AMBIENT, light->ambient);
}

/**
 * @brief Updates the diffuse color of a Light source.
 *
 * @param light   The Light source to update.
 */
void updateDiffuse(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_DIFFUSE, light->diffuse);
}

/**
 * @brief Updates the specular color of a Light source.
 *
 * @param light    The Light source to update.
 */
void updateSpecular(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_SPECULAR, light->specular);
}

/**
 * @brief Updates the properties of a Light source.
 *
 * @param light The Light source to update.
 */
void updateLight(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_AMBIENT, light->ambient);
	glLightfv(GL_LIGHT0 + light->id, GL_DIFFUSE, light->diffuse);
	glLightfv(GL_LIGHT0 + light->id, GL_SPECULAR, light->specular);
	glLightfv(GL_LIGHT0 + light->id, GL_POSITION, light->position);
}