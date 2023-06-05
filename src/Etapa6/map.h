#pragma once

#include "base.h"
#include "texture.h"

typedef struct Room
{
	float width;
	float height;
	float depth;
	float wall_thickness;
	struct Color4f back_wall_color;
	struct Color4f right_wall_color;
	struct Color4f left_wall_color;
	struct Color4f top_wall_color;
	struct Color4f bottom_wall_color;
	Texture *wall_texture;
} Room;

void init_room(Room *room, Texture *text);
void draw_room(Room *room);
