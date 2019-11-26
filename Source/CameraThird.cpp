#include "CameraThird.h"
#include "Setup.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace glm;

CameraThird* CameraThird::instance = 0;
const float CameraThird::FOV = 70.0;
const float CameraThird::NEAR = 0.01;
const float CameraThird::FAR = 1000.0;
vec3 CameraThird::cPosition = vec3(0);
vec3 CameraThird::cLookAt = vec3(0);
vec3 CameraThird::cUp = vec3(0);
float CameraThird::cameraHorizontalAngle = 90.0f;
float CameraThird::cameraVerticalAngle = 0.0f;
const float CameraThird::CAMERA_ANGULAR_SPEED = 10.0f;
const float CameraThird::VERTICAL_CLAMP = 89.0f;

CameraThird& CameraThird::getInstance(vec3 position, vec3 lookAt, vec3 up) {
	if (instance == 0) instance = new CameraThird(position, lookAt, up);
	return *instance;
}

vec3 CameraThird::getCameraSideVector() {
	return normalize(cross(getCameraFrontVector(), vec3(0.0f, 1.0f, 0.0f)));
}

vec3 CameraThird::getCameraFrontVector() {
	vec3 lookAt = getLookAt();
	vec3 front = vec3(lookAt.x, 0, lookAt.z);
	return normalize(front);
}

CameraThird::CameraThird(vec3 position, vec3 lookAt, vec3 up) {
	cPosition = position;
	cLookAt = lookAt;
	cUp = up;
}

mat4 CameraThird::getViewMatrix() {
	return lookAt(cPosition, cPosition + cLookAt, cUp);
}

mat4 CameraThird::getProjMatrix() {
	return perspective(FOV, (float) Setup::SCREEN_WIDTH / (float) Setup::SCREEN_HEIGHT, NEAR, FAR);
}

void CameraThird::updatePosition(vec3 position, vec3 lookAt, vec3 up) {
	cPosition = position;
	cLookAt = lookAt;
	cUp = up;
}

vec3 CameraThird::getPosition() {
	return cPosition;
}

vec3 CameraThird::getLookAt() {
	return cLookAt;
}

vec3 CameraThird::getUpVector() {
	return cUp;
}
