/**
 * @file
 * @brief Defines a Light structure and related functions for managing lights.
 */
#pragma once

/**
 * @struct Light
 * @brief Represents a light source.
 */
typedef struct Light
{
	int id;			   // The unique identifier of the light source.
	bool status;	   // Indicates whether the light is turned on or off.
	float ambient[4];  // The ambient color of the light in RGBA format.
	float diffuse[4];  // The diffuse color of the light in RGBA format.
	float specular[4]; // The specular color of the light in RGBA format.
	float position[4]; // The position of the light in homogeneous coordinates.
} Light;

/**
 * @brief Turns on a light source.
 * @param light A pointer to the Light structure to turn on.
 */
void on(Light *light);

/**
 * @brief Turns off a light source.
 * @param light A pointer to the Light structure to turn off.
 */
void off(Light *light);

/**
 * @brief Updates the position of a light source.
 * @param light A pointer to the Light structure to update.
 */
void updatePosition(Light *light);

/**
 * @brief Updates the ambient color of a light source.
 * @param light A pointer to the Light structure to update.
 */
void updateAmbient(Light *light);

/**
 * @brief Updates the diffuse color of a light source.
 * @param light A pointer to the Light structure to update.
 */
void updateDiffuse(Light *light);

/**
 * @brief Updates the specular color of a light source.
 * @param light A pointer to the Light structure to update.
 */
void updateSpecular(Light *light);

/**
 * @brief Updates the properties of a Light source.
 * @param light The Light source to update.
 */
void updateLight(Light *light);
