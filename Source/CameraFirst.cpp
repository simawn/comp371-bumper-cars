#include "CameraFirst.h"

using namespace glm;

CameraFirst* CameraFirst::instance = 0;
const float CameraFirst::FOV = 70.0;
const float CameraFirst::NEAR = 0.01;
const float CameraFirst::FAR = 1000.0;
vec3 CameraFirst::cPosition = vec3(0);
vec3 CameraFirst::cLookAt = vec3(0);
vec3 CameraFirst::cUp = vec3(0);
float CameraFirst::cameraHorizontalAngle = 90.0f;
float CameraFirst::cameraVerticalAngle = 0.0f;
const float CameraFirst::CAMERA_ANGULAR_SPEED = 5.0f;
const float CameraFirst::VERTICAL_CLAMP = 75.0f;

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

void CameraFirst::updateInput(ModelBumperCar* cameraBumperCar) {
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

	/*
	updatePosition(getPosition(),
		vec3(cosf(theta)*cosf(phi), sinf(phi), -sinf(theta)*cosf(phi)),
		getUpVector());
	*/
	
	
	float cameraHeight = 3.0f;

	vec3 cameraPosition = cameraBumperCar->GetPosition() + vec3(0.0f, cameraHeight, 0.0f) + rotate(vec3(0.0f, 0.0f, 2.0f), radians(cameraBumperCar->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f));

	updatePosition(	
		//Position
		cameraPosition,
		//Look at
		cameraPosition + vec3(cosf(theta)*cosf(phi), sinf(phi), -sinf(theta)*cosf(phi)),
		//Up
		vec3(0.0f, 1.0f, 0.0f));
}
