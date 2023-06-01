#include "camera.h"
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

void initCamera(Camera *cam)
{
	cam->yaw = 0.0f;
	cam->pitch = 0.0f;
	cam->position = (Vector3f){0.0f, 0.0f, 5.0f};
	cam->lookingAt = (Vector3f){
		.x = cam->position.x + sin(cam->yaw),
		.y = cam->position.y + sin(cam->pitch),
		.z = cam->position.z - cos(cam->yaw)};
	cam->up = (Vector3f){0.0f, 1.0f, 0.0f};
}

void calcTargetPoint(Camera *cam, float *x, float *y, float *z)
{
	*x = cam->position.x + sin(cam->yaw);
	*y = cam->position.y + sin(cam->pitch);
	*z = cam->position.z - cos(cam->yaw);
}

void updateCamera(Camera *cam)
{
	float lookingAtX;
	float lookingAtY;
	float lookingAtZ;
	calcTargetPoint(cam, &lookingAtX, &lookingAtY, &lookingAtZ);

	gluLookAt(cam->position.x, cam->position.y, cam->position.z,
			  lookingAtX, lookingAtY, lookingAtZ,
			  cam->up.x, cam->up.y, cam->up.z);
}

void rotateCameraRight(Camera *cam, float angle)
{
	cam->yaw += angle;
}

void rotateCameraLeft(Camera *cam, float angle)
{
	cam->yaw -= angle;
}

void rotateCameraUp(Camera *cam, float angle)
{
	cam->pitch += angle;
}

void rotateCameraDown(Camera *cam, float angle)
{
	cam->pitch -= angle;
}

void moveCameraUp(Camera *cam, float inc)
{
	cam->position.y += inc;
}

void moveCameraDown(Camera *cam, float inc)
{
	cam->position.y -= inc;
}

void moveCameraForward(Camera *cam, float inc)
{
	cam->position.x -= inc * sin(cam->yaw);
	cam->position.z -= inc * cos(cam->yaw);
}
void moveCameraBackward(Camera *cam, float inc)
{
	cam->position.x += inc * sin(cam->yaw);
	cam->position.z += inc * cos(cam->yaw);
}

void starfeCameraRight(Camera *cam, float inc)
{
	cam->position.x += inc * cos(cam->yaw);
	cam->position.z -= inc * sin(cam->yaw);
}

void starfeCameraLeft(Camera *cam, float inc)
{
	cam->position.x -= inc * cos(cam->yaw);
	cam->position.z += inc * sin(cam->yaw);
}

void printCamera(Camera *cam)
{
	printf("Camera:\n");
	printf("\tYaw: %f\n", cam->yaw);
	printf("\tPitch: %f\n", cam->pitch);
	printf("\tPosition: (%f, %f, %f)\n", cam->position.x, cam->position.y, cam->position.z);
	printf("\tLookingAt: (%f, %f, %f)\n", cam->lookingAt.x, cam->lookingAt.y, cam->lookingAt.z);
	printf("\tUp: (%f, %f, %f)\n", cam->up.x, cam->up.y, cam->up.z);
	printf("\n");
}
