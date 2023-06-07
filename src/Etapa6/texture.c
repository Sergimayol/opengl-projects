#include "texture.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void init_texture(Texture *texture)
{
	texture->textureId = 0;
}

void load_texture(Texture *texture, const char *textPath)
{
	int width, height, channels;
	unsigned char* image = stbi_load(textPath, &width, &height, &channels, STBI_rgb);
	if (!image)
    {
        printf("[ERROR]: Failed to load image %s\n", textPath);
        return;
    }
	printf("[DEBUG]: Loading image %s with %d channels done\n", textPath, channels);

    // Generate and bind a texture object
    glGenTextures(1, &texture->textureId);
	printf("[DEBUG]: Texture id(%d) assigned\n", texture->textureId);
    glBindTexture(GL_TEXTURE_2D, texture->textureId);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image)
    {
		texture->image = image;
		printf("[DEBUG]: Saving image with size(%dx%d) to struct done\n", width, height);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		printf("[DEBUG]: Loading texture to OpenGL done\n");
    }
	else
	{
        printf("[ERROR]: Failed to load image %s\n", textPath);
	}

    // Free the image data
	stbi_image_free(image);
	printf("[DEBUG]: Free image data done\n");
}

