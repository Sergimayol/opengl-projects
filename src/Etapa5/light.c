#include <stdbool.h>
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
 * @brief Creates a new Light struct with the given parameters.
 *
 * @param id The ID of the light source.
 * @param status The status of the light source (on/off).
 * @param ambient The ambient light color.
 * @param diffuse The diffuse light color.
 * @param specular The specular light color.
 * @param position The position of the light source.
 * @return The created Light struct.
 */
Light createLight(int id, bool status, float ambient[4], float diffuse[4], float specular[4], float position[4])
{
	Light light;
	light.id = id;
	light.status = status;
	memcpy(light.ambient, ambient, sizeof(float) * 4);
	memcpy(light.diffuse, diffuse, sizeof(float) * 4);
	memcpy(light.specular, specular, sizeof(float) * 4);
	memcpy(light.position, position, sizeof(float) * 4);
	return light;
}

/**
 * @brief Updates the color properties of a Light source.
 *
 * @param light The Light source to update.
 * @param color The new color values [r, g, b, a].
 */
void updateColor(Light *light, GLfloat color[4])
{
	for (int i = 0; i < 4; i++)
		light->diffuse[i] = light->specular[i] = color[i];

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
 * @brief Updates the position of a Light source.
 *
 * @param light    The Light source to update.
 * @param position The new position values [x, y, z, w].
 */
void updatePosition(Light *light, GLfloat position[4])
{
	for (int i = 0; i < 4; i++)
		light->position[i] = position[i];
	glLightfv(GL_LIGHT0 + light->id, GL_POSITION, light->position);
}

/**
 * @brief Updates the ambient color of a Light source.
 *
 * @param light   The Light source to update.
 * @param ambient The new ambient color values [r, g, b, a].
 */
void updateAmbient(Light *light, GLfloat ambient[4])
{
	for (int i = 0; i < 4; i++)
		light->ambient[i] = ambient[i];
	glLightfv(GL_LIGHT0 + light->id, GL_AMBIENT, light->ambient);
}

/**
 * @brief Updates the diffuse color of a Light source.
 *
 * @param light   The Light source to update.
 * @param diffuse The new diffuse color values [r, g, b, a].
 */
void updateDiffuse(Light *light, GLfloat diffuse[4])
{
	for (int i = 0; i < 4; i++)
		light->diffuse[i] = diffuse[i];
	glLightfv(GL_LIGHT0 + light->id, GL_DIFFUSE, light->diffuse);
}

/**
 * @brief Updates the specular color of a Light source.
 *
 * @param light    The Light source to update.
 * @param specular The new specular color values [r, g, b, a].
 */
void updateSpecular(Light *light, GLfloat specular[4])
{
	for (int i = 0; i < 4; i++)
		light->specular[i] = specular[i];
	glLightfv(GL_LIGHT0 + light->id, GL_SPECULAR, light->specular);
}

/**
 * @brief Updates the properties of a Light source.
 *
 * @param light The Light source to update.
 */
void update(Light *light)
{
	glLightfv(GL_LIGHT0 + light->id, GL_AMBIENT, light->ambient);
	glLightfv(GL_LIGHT0 + light->id, GL_DIFFUSE, light->diffuse);
	glLightfv(GL_LIGHT0 + light->id, GL_SPECULAR, light->specular);
	glLightfv(GL_LIGHT0 + light->id, GL_POSITION, light->position);
}