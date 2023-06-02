#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdbool.h>

typedef struct Object
{
	const struct aiScene *scene;
	struct aiMesh *mesh;
	struct aiMaterial *material;
	const char *objPath;
} Object;

void init_object(Object *object);
void load_object(Object *object);
void draw_object(Object *object, bool getMaterial, bool getNormals);
