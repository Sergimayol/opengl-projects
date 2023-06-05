#include "texture.h"
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void init_texture_counter_id(TextureIdCounter *counterId)
{
	counterId->counterId = 0;
}

void init_texture(Texture *texture, TextureIdCounter *counterId)
{
	counterId->counterId += 1;
	texture->textureId = counterId->counterId;
}

void load_texture(Texture *texture, const char *textPath)
{
	int width, height, channels;
	unsigned char* image = stbi_load(textPath, &width, &height, &channels, 0);

    // Generate and bind a texture object
    glGenTextures(texture->textureId, &texture->textureId);
    glBindTexture(GL_TEXTURE_2D, texture->textureId);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture->image = image;

    // Load the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Free the image data
	stbi_image_free(image);
}

