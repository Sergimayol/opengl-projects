#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const struct aiScene *scene = NULL;
struct aiMesh *modelMesh = NULL;
const char *modelFile = "/mnt/c/Users/ruben/Documents/Github/opengl-projects/src/Etapa6/objetos/book/book.obj";

const int W_WIDTH = 600;
const int W_HEIGHT = 600;
float fAngle = 0.0f;

void loadModel(const char *filePath)
{
	scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (!scene)
	{
		printf("Error loading model: %s\n", aiGetErrorString());
		exit(1);
	}
	modelMesh = scene->mMeshes[0]; // Assuming there is only one mesh in the scene
}
void renderScene()
{
	// Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set up your camera and other transformations
	gluLookAt(0.0, 0.0, 5.0,  // eye position
			  0.0, 0.0, 0.0,  // lookat position
			  0.0, 1.0, 0.0); // up direction

	// Set the color
	glColor3f(1.0, 0.0, 0.0);

	// Render the loaded model
	glRotatef(fAngle, 0.0, 1.0, 0.0);
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

	// Swap the buffers
	glutSwapBuffers();
}

void idle()
{
	// Incrementamos el ángulo
	fAngle += 0.1f;
	// Si es mayor que dos pi la decrementamos
	if (fAngle > 360)
		fAngle -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
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
{
	// Inicializamos la librería GLUT
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
	glutIdleFunc(idle);

	glClear(GL_COLOR_BUFFER_BIT);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();

	return 0;
}
