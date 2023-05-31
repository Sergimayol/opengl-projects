/**
@file
@brief Defines a Light structure and related functions for managing lights.
*/
#pragma once

/**
@struct Light
@brief Represents a light source.
*/
typedef struct
{
	int id;			   ///< The unique identifier of the light source.
	bool status;	   ///< Indicates whether the light is turned on or off.
	float ambient[4];  ///< The ambient color of the light in RGBA format.
	float diffuse[4];  ///< The diffuse color of the light in RGBA format.
	float specular[4]; ///< The specular color of the light in RGBA format.
	float position[4]; ///< The position of the light in homogeneous coordinates.
} Light;

/**
@brief Updates the color of a light source.
@param light A pointer to the Light structure to update.
@param color An array containing the new color values in RGBA format.
*/
void updateColor(Light light, float color[4]);

/**
@brief Turns on a light source.
@param light A pointer to the Light structure to turn on.
*/
void on(Light light);

/**
@brief Turns off a light source.
@param light A pointer to the Light structure to turn off.
*/
void off(Light light);

/**
@brief Updates the position of a light source.
@param light A pointer to the Light structure to update.
@param position An array containing the new position values in homogeneous coordinates.
*/
void updatePosition(Light light, float position[4]);

/**
@brief Updates the ambient color of a light source.
@param light A pointer to the Light structure to update.
@param ambient An array containing the new ambient color values in RGBA format.
*/
void updateAmbient(Light light, float ambient[4]);

/**
@brief Updates the diffuse color of a light source.
@param light A pointer to the Light structure to update.
@param diffuse An array containing the new diffuse color values in RGBA format.
*/
void updateDiffuse(Light light, float diffuse[4]);

/**
@brief Updates the specular color of a light source.
@param light A pointer to the Light structure to update.
@param specular An array containing the new specular color values in RGBA format.
*/
void updateSpecular(Light light, float specular[4]);