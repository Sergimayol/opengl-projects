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
	object->material = NULL;
}

void load_object(Object *object)
{
	object->scene = aiImportFile(object->objPath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (!object->scene)
	{
		printf("Error loading model: %s\n", aiGetErrorString());
		exit(1);
	}
	object->mesh = object->scene->mMeshes[0];									// Assuming there is only one mesh in the scene
	object->material = object->scene->mMaterials[object->mesh->mMaterialIndex]; // Assign material
}

void draw_object(Object *object)
{
	const struct aiMesh *modelMesh = object->mesh;
	const struct aiMaterial *material = object->material;

	// Set material properties
	struct aiColor4D ambientColor;
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor))
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambientColor);

	struct aiColor4D diffuseColor;
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor))
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&diffuseColor);

	struct aiColor4D specularColor;
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor))
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&specularColor);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
	for (unsigned int i = 0; i < modelMesh->mNumFaces; ++i)
	{
		const struct aiFace *face = &modelMesh->mFaces[i];
		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < face->mNumIndices; ++j)
		{
			unsigned int vertexIndex = face->mIndices[j];

			// Retrieve vertex position
			struct aiVector3D vertex = modelMesh->mVertices[vertexIndex];
			glVertex3f(vertex.x, vertex.y, vertex.z);

			// Retrieve vertex normal
			struct aiVector3D normal = modelMesh->mNormals[vertexIndex];
			glNormal3f(normal.x, normal.y, normal.z);
		}
		glEnd();
	}
}