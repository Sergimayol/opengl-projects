#pragma once

typedef struct Vector3f
{
	float x;
	float y;
	float z;
} Vector3f;

typedef struct Camera
{
	Vector3f position;	// Posición de la cámara
	Vector3f lookingAt; // Punto donde se está observando
	Vector3f up;		// Dirección de la parte superior de la cámara
	float yaw;			// yaw ángulo (rotación izq/der)
	float pitch;		// Pitch ángulo (rotación arriba/abajo)
} Camera;

/// Inicializa los valores de la cámara a unos por defecto
void initCamera(Camera *cam);
/// Calcula el punto donde se desea / tiene que mirar
void calcTargetPoint(Camera *cam, float *x, float *y, float *z);
/// Permite rotar la cámara hacia la derecha dado un cierto ángulo / valor
void rotateCameraRight(Camera *cam, float angle);
/// Permite rotar la cámara hacia la izquierda dado un cierto ángulo / valor
void rotateCameraLeft(Camera *cam, float angle);
/// Permite rotar la cámara hacia arriba dado un cierto ángulo / valor
void rotateCameraUp(Camera *cam, float angle);
/// Permite rotar la cámara hacia abajo dado un cierto ángulo / valor
void rotateCameraDown(Camera *cam, float angle);
/// Permite mover la cámara hacia abajo dado un cierto ángulo / valor
void moveCameraUp(Camera *cam, float inc);
/// Permite mover la cámara hacia abajo dado un cierto ángulo / valor
void moveCameraDown(Camera *cam, float inc);
/// Permite mover la cámara frontalmente dado un cierto ángulo / valor
void moveCameraForward(Camera *cam, float inc);
/// Permite mover la cámara posteriormente dado un cierto ángulo / valor
void moveCameraBackward(Camera *cam, float inc);
/// Permite mover lateralmente la cámara hacia la izquierda dado un cierto ángulo / valor
void starfeCameraRight(Camera *cam, float inc);
/// Permite mover lateralmente la cámara hacia la derecha dado un cierto ángulo / valor
void starfeCameraLeft(Camera *cam, float inc);
/// Hace un print de todos los valores de la cámara
void printCamera(Camera *cam);
