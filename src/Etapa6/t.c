#include <GL/glut.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *modelFile = "/mnt/c/Users/ruben/Documents/Github/opengl-projects/src/Etapa6/objetos/book/book.obj";
const struct aiScene *scene = NULL;
struct aiMesh *modelMesh = NULL;
unsigned int *textureIDs = NULL;
unsigned int numTextures = 0;

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
void loadModel()
{
	const struct aiScene *scene = aiImportFile(modelFile, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Error loading model: %s\n", aiGetErrorString());
		exit(1);
	}

	// Process the textures
	if (scene->mNumTextures > 0)
	{
		// Load textures for each material in the scene
		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
		{
			const struct aiMaterial *material = scene->mMaterials[i];
			struct aiString texturePath;
			if (aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE) > 0)
			{
				aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL, NULL);
				unsigned char *image = stbi_load(texturePath.data, NULL, NULL, NULL, STBI_rgb);
				if (!image)
				{
					printf("Error loading texture: %s\n", stbi_failure_reason());
					exit(1);
				}

				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene->mTextures[i]->mWidth, scene->mTextures[i]->mHeight,
							 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(GL_TEXTURE_2D);

				// Set texture parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(image);

				// Use the texture for rendering
				// ...
			}
		}
	}
}

void renderScene()
{
	// Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set up your camera and other transformations

	// Render the loaded model
	for (unsigned int i = 0; i < modelMesh->mNumFaces; ++i)
	{
		const struct aiFace *face = &modelMesh->mFaces[i];
		unsigned int textureIndex = modelMesh->mMaterialIndex;
		glBindTexture(GL_TEXTURE_2D, textureIDs[textureIndex]);

		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < face->mNumIndices; ++j)
		{
			unsigned int vertexIndex = face->mIndices[j];
			struct aiVector3D vertex = modelMesh->mVertices[vertexIndex];
			struct aiVector3D texCoord = modelMesh->mTextureCoords[0][vertexIndex];
			glTexCoord2f(texCoord.x, texCoord.y);
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
	}

	// Swap the buffers
	glutSwapBuffers();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width / (double)height, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{ // Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	loadModel(modelFile);

	// Creamos la nueva ventana
	glutCreateWindow("mierda");
	glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST | GL_COLOR_MATERIAL);

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);

	glClear(GL_COLOR_BUFFER_BIT);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}
