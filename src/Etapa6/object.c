#include "object.h"
#include <GL/glut.h>
#include <stdio.h>

void init_object(Object *object)
{
	object->scene = NULL;
	object->mesh = NULL;
	object->material = NULL;
	object->textures = NULL;
}

void load_object(Object *object)
{
	object->scene = aiImportFile(object->objPath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (!object->scene)
	{
		printf("Error loading model: %s\n", aiGetErrorString());
		exit(1);
	}
	printf("[DEBUG]: Loading model %s done\n", object->objPath);
	object->mesh = object->scene->mMeshes[0];									// Assuming there is only one mesh in the scene
	printf("[DEBUG]: Loding mesh done\n");
	object->material = object->scene->mMaterials[object->mesh->mMaterialIndex]; // Assign material
	printf("[DEBUG]: Material assignment done\n");
}

void draw_object(Object *object, bool getMaterial, bool getNormals)
{
	const struct aiMesh *modelMesh = object->mesh;
	if (getMaterial)
	{
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
	}
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

			if (getNormals)
			{
				// Retrieve vertex normal
				struct aiVector3D normal = modelMesh->mNormals[vertexIndex];
				glNormal3f(normal.x, normal.y, normal.z);
			}
		}
		glEnd();
	}
}
