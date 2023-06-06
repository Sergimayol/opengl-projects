#pragma once

#include <GL/gl.h>

typedef struct Texture
{
	GLuint textureId;
	const unsigned char* image;
} Texture;

void init_texture(Texture *texture);
void load_texture(Texture *texture, const char *textPath);
