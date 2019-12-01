#include "CameraThird.h"

using namespace glm;
using namespace std;

CameraThird* CameraThird::instance = 0;
const float CameraThird::FOV = 70.0;
const float CameraThird::NEAR = 0.01;
const float CameraThird::FAR = 1000.0;
vec3 CameraThird::cPosition = vec3(0);
vec3 CameraThird::cLookAt = vec3(0);
vec3 CameraThird::cUp = vec3(0);
float CameraThird::cameraHorizontalAngle = 89.0f;
float CameraThird::cameraVerticalAngle = -60.0f;
const float CameraThird::CAMERA_ANGULAR_SPEED = 5.0f;
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

void CameraThird::reset() {
	cameraHorizontalAngle = 89.0f;
	cameraVerticalAngle = -60.0f;
	cPosition = vec3(0, 50, 40);
	cLookAt = vec3(0, 0, 0);
	cUp = vec3(0, 1, 0);
}

void CameraThird::updateInput() {
	double dx = IO::getMouseMoveDifference().first;
	double dy = IO::getMouseMoveDifference().second;

	cameraHorizontalAngle -= dx * CAMERA_ANGULAR_SPEED * Renderer::tick;
	cameraVerticalAngle -= dy * CAMERA_ANGULAR_SPEED * Renderer::tick;

	//Clamp verticle angle
	cameraVerticalAngle = std::max(-VERTICAL_CLAMP, std::min(VERTICAL_CLAMP, cameraVerticalAngle));

	//Avoid overflow
	if (cameraHorizontalAngle > 360) cameraHorizontalAngle -= 360;
	else if (cameraHorizontalAngle < -360) cameraHorizontalAngle += 360;

	float theta = radians(cameraHorizontalAngle);
	float phi = radians(cameraVerticalAngle);

	updatePosition(getPosition(),
		vec3(cosf(theta)*cosf(phi), sinf(phi), -sinf(theta)*cosf(phi)),
		getUpVector());
}
