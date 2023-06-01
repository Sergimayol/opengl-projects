#include "object.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glut.h>
#include <stdio.h>

void init_object(Object *object)
{
	object->scene = NULL;
	object->mesh = NULL;
}

void load_object(Object *object, const char *filePath)
{
	object->scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (!object->scene)
	{
		printf("Error loading model: %s\n", aiGetErrorString());
		exit(1);
	}
	object->mesh = object->scene->mMeshes[0]; // Assuming there is only one mesh in the scene
}

void draw_object(Object *object)
{
	const struct aiMesh *modelMesh = object->mesh;
	for (unsigned int i = 0; i < modelMesh->mNumFaces; ++i)
	{
		const struct aiFace *face = &modelMesh->mFaces[i];
		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < face->mNumIndices; ++j)
		{
			unsigned int vertexIndex = face->mIndices[j];
			struct aiVector3D vertex = modelMesh->mVertices[vertexIndex];
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
	}
}