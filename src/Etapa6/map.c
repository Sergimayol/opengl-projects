#include "map.h"
#include "base.h"
#include "texture.h"
#include <GL/gl.h>
#include <stdlib.h>

void init_room(Room *room, Texture *text)
{
	room->width = 6.5f;
	room->height = 3.5f;
	room->depth = 6.5f;
	room->wall_thickness = 0.5f;
	room->top_wall_color = (struct Color4f){PURE_WHITE};
	room->bottom_wall_color = (struct Color4f){PURE_WHITE};
	room->back_wall_color = (struct Color4f){PURE_WHITE};
	room->right_wall_color = (struct Color4f){PURE_WHITE};
	room->left_wall_color = (struct Color4f){PURE_WHITE};
	room->wall_texture = text;
}

void draw_room(Room *room)
{
	float width = room->width;
	float height = room->height;
	float depth = room->depth;
	float thickness = room->wall_thickness;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, room->wall_texture->textureId);
	/*
    // Front wall
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, -height / 2, depth / 2 - thickness);
    glVertex3f(width / 2, -height / 2, depth / 2 - thickness);
    glVertex3f(width / 2, height / 2, depth / 2 - thickness);
    glVertex3f(-width / 2, height / 2, depth / 2 - thickness);
    glEnd();
	*/

    // Back wall
    glBegin(GL_QUADS);
	glColor3f(room->back_wall_color.r, room->back_wall_color.g, room->back_wall_color.b);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2, -height / 2, -depth / 2);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2, height / 2, -depth / 2);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glEnd();

    // Left wall
    glBegin(GL_QUADS);
	glColor3f(room->left_wall_color.r, room->left_wall_color.g, room->left_wall_color.b);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-width / 2, height / 2, -depth / 2);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2, height / 2, depth / 2 - thickness);
    glEnd();

    // Right wall
    glBegin(GL_QUADS);
	glColor3f(room->right_wall_color.r, room->right_wall_color.g, room->right_wall_color.b);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(width / 2, -height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2, -height / 2, -depth / 2);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2, height / 2, -depth / 2);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(width / 2, height / 2, depth / 2 - thickness);
    glEnd();

    // Floor
    glBegin(GL_QUADS);
	glColor3f(room->bottom_wall_color.r, room->bottom_wall_color.g, room->bottom_wall_color.b);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2, -height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2, -height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2, -height / 2, -depth / 2);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glEnd();

    // Ceiling
    glBegin(GL_QUADS);
	glColor3f(room->top_wall_color.r, room->top_wall_color.g, room->top_wall_color.b);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-width / 2, height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(width / 2, height / 2, depth / 2 - thickness);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(width / 2, height / 2, -depth / 2);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-width / 2, height / 2, -depth / 2);
	glEnd();
    glDisable(GL_TEXTURE_2D);
}
