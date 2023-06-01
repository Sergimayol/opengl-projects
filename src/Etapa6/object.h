#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

typedef struct Object
{
	const struct aiScene *scene;
	struct aiMesh *mesh;
} Object;

void init_object(Object *object);
void load_object(Object *object, const char *filePath);
void draw_object(Object *object);
