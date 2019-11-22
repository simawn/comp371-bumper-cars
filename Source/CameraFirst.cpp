#include "CameraFirst.h"
#include "Setup.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace glm;

CameraFirst* CameraFirst::instance = 0;
const float CameraFirst::FOV = 70.0;
const float CameraFirst::NEAR = 0.01;
const float CameraFirst::FAR = 1000.0;
vec3 CameraFirst::cPosition = vec3(0);
vec3 CameraFirst::cLookAt = vec3(0);
vec3 CameraFirst::cUp = vec3(0);

CameraFirst & CameraFirst::getInstance(vec3 position, vec3 lookAt, vec3 up) {
	if (instance == 0) instance = new CameraFirst(position, lookAt, up);
	return *instance;
}

CameraFirst::CameraFirst(vec3 position, vec3 lookAt, vec3 up) {
	cPosition = position;
	cLookAt = lookAt;
	cUp = up;
}

mat4 CameraFirst::getViewMatrix() {
	return lookAt(cPosition, cLookAt, cUp);
}

mat4 CameraFirst::getProjMatrix() {
	return perspective(FOV, (float) Setup::SCREEN_WIDTH / (float) Setup::SCREEN_HEIGHT, NEAR, FAR);
}

void CameraFirst::updatePosition(vec3 position, vec3 lookAt, vec3 up) {
	cPosition = position;
	cLookAt = lookAt;
	cUp = up;
}

vec3 CameraFirst::getPosition() {
	return cPosition;
}

vec3 CameraFirst::getLookAt() {
	return cLookAt;
}

vec3 CameraFirst::getUpVector() {
	return cUp;
}
