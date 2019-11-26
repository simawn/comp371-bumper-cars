#include "IO.h"
#include "Setup.h"
#include "CameraThird.h"
#include "Renderer.h"
#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

IO* IO::instance = 0;
bool IO::stopSimulation = false;
bool IO::stopLights = false;
bool IO::isFirstCamera = false;

IO& IO::getInstance() {
	if (instance == 0) instance = new IO();
	return *instance;
}

void IO::updateMousePosition() {
	getCurrentMousePosition();
}

pair<double, double> IO::getCurrentMousePosition() {
	lastMousePosX = currentMousePosX;
	lastMousePosY = currentMousePosY;
	glfwGetCursorPos(Setup::window, &currentMousePosX, &currentMousePosY);
	return make_pair(currentMousePosX, currentMousePosY);
}

pair<double, double> IO::getLastMousePosition() {
	return make_pair(lastMousePosX, lastMousePosY);
}

pair<double, double> IO::getMouseMoveDifference() {
	return make_pair(currentMousePosX - lastMousePosX, currentMousePosY - lastMousePosY);
}

void IO::processInputs() {

	glfwPollEvents();

	if (glfwGetKey(Setup::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Setup::window, true);

	if (glfwGetKey(Setup::window, GLFW_KEY_W) == GLFW_PRESS) {
		updateCameraPosition(0);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_S) == GLFW_PRESS) {
		updateCameraPosition(1);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_A) == GLFW_PRESS) {
		updateCameraPosition(2);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_D) == GLFW_PRESS) {
		updateCameraPosition(3);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		updateCameraPosition(4);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		updateCameraPosition(5);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_HOME) == GLFW_PRESS) {
	}

	if (glfwGetMouseButton(Setup::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (!isFirstCamera) {
			float moveDiffY = getMouseMoveDifference().second;
			vec3 cPos = CameraThird::getPosition();
			vec3 cLookAt = CameraThird::getLookAt();
			vec3 cUp = CameraThird::getUpVector();
			float tick = Renderer::tick;
			vec3 moveSpeed = vec3(1.0f + (moveDiffY * tick));

			CameraThird::updatePosition(cPos * moveSpeed, cLookAt * moveSpeed, cUp * moveSpeed);
		}
	}

	if (glfwGetMouseButton(Setup::window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
	}

	if (glfwGetMouseButton(Setup::window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
	}

	//Stop movement
	if (lastHState == GLFW_RELEASE && glfwGetKey(Setup::window, GLFW_KEY_H) == GLFW_PRESS) {
		stopSimulation = !stopSimulation;
	}
	lastHState = glfwGetKey(Setup::window, GLFW_KEY_H);

	//Toggle lights
	if (lastLState == GLFW_RELEASE && glfwGetKey(Setup::window, GLFW_KEY_L) == GLFW_PRESS) {
		stopLights = !stopLights;
	}
	lastLState = glfwGetKey(Setup::window, GLFW_KEY_L);

	//Toggle camera
	if (lastCState == GLFW_RELEASE && glfwGetKey(Setup::window, GLFW_KEY_C) == GLFW_PRESS) {
		isFirstCamera = !isFirstCamera;
	}
	lastCState = glfwGetKey(Setup::window, GLFW_KEY_C);
}

void IO::updateCameraPosition(int dir) {
	if (!isFirstCamera) {
		vec3 cPos = CameraThird::getPosition();
		vec3 cLookAt = CameraThird::getLookAt();
		vec3 cUp = CameraThird::getUpVector();

		vec3 sideVector = CameraThird::getCameraSideVector();
		vec3 frontVector = CameraThird::getCameraFrontVector();

		float extraSpeed = glfwGetKey(Setup::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ? 5 : 1;
		float tick = Renderer::tick;
		float moveSpeed = tick * CAM_SPEED * extraSpeed;

		switch (dir) {
		case 0: //northSouth W
			cPos += frontVector * moveSpeed;
			break;
		case 1: //northSouth S
			cPos -= frontVector * moveSpeed;
			break;
		case 2: //eastWest A
			cPos -= sideVector * moveSpeed;
			break;
		case 3: //eastWest D
			cPos += sideVector * moveSpeed;
			break;
		case 4: //up
			cPos += vec3(0.0f, moveSpeed, 0.0f);
			break;
		case 5: //down
			cPos -= vec3(0.0f, moveSpeed, 0.0f);
			break;
		}

		CameraThird::updatePosition(cPos, cLookAt, cUp);
	}
}

IO::IO() {}
