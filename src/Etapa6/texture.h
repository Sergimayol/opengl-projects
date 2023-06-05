#pragma once

#include <GL/gl.h>

typedef struct TextureIdCounter
{
	GLuint counterId; // > 0
} TextureIdCounter;

typedef struct Texture
{
	GLuint textureId;
	const unsigned char* image;
} Texture;

void init_texture_counter_id(TextureIdCounter *counterId);
void init_texture(Texture *texture, TextureIdCounter *counterId);
void load_texture(Texture *texture, const char *textPath);
