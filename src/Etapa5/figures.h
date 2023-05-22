#pragma once
#include <GL/gl.h>

// Esta función permite dibujar una tetera en 3D
void drawTeapot(const GLdouble size, float rotationAngle,
                float rotationCoords[], bool displayWired,
                struct Color3f figColor);

// Esta función permite dibujar un donut en 3D
void drawDonut(const GLdouble size, const int slices,
               float rotationAngle, float rotationCoords[],
               bool displayWired, struct Color3f figColor);
