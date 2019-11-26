#pragma once

#include "Setup.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

class CameraThird {
public:
	static CameraThird& getInstance(vec3 position, vec3 lookAt, vec3 up);
	
	static mat4 getViewMatrix();
	static mat4 getProjMatrix();
	static void updatePosition(vec3 position, vec3 lookAt, vec3 up);
	static vec3 getPosition();
	static vec3 getLookAt();
	static vec3 getUpVector();
	static float cameraHorizontalAngle;
	static float cameraVerticalAngle;
	static const float CAMERA_ANGULAR_SPEED;
	static const float VERTICAL_CLAMP;
	static vec3 getCameraSideVector();
	static vec3 getCameraFrontVector();
private:
	CameraThird(vec3 position, vec3 lookAt, vec3 up);
	static CameraThird* instance;
	static vec3 cPosition;
	static vec3 cLookAt;
	static vec3 cUp;
	const static float FOV;
	const static float NEAR;
	const static float FAR;
};
