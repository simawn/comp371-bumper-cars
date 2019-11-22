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

	if (glfwGetKey(Setup::window, GLFW_KEY_UP) == GLFW_PRESS) {
		updateCameraPosition(0);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		updateCameraPosition(1);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		updateCameraPosition(2);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		updateCameraPosition(3);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		updateCameraPosition(4);
	}

	if (glfwGetKey(Setup::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
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
		int eastWest = 0;
		int northSouth = 0;
		int upDown = 0;

		switch (dir) {
		case 0:
			northSouth = -1;
			break;
		case 1:
			northSouth = 1;
			break;
		case 2:
			eastWest = -1;
			break;
		case 3:
			eastWest = 1;
			break;
		case 4:
			upDown = 1;
			break;
		case 5:
			upDown = -1;
			break;
		}
		vec3 cPos = CameraThird::getPosition();
		vec3 cLookAt = CameraThird::getLookAt();
		vec3 cUp = CameraThird::getUpVector();
		float tick = Renderer::tick;
		float moveSpeed = tick * CAM_SPEED;

		vec3 newCPos = vec3(cPos.x + eastWest * (moveSpeed),
							cPos.y + upDown * (moveSpeed),
							cPos.z + northSouth * (moveSpeed));

		vec3 newCLookAt = vec3(cLookAt.x + eastWest * (moveSpeed),
							   cLookAt.y + upDown * (moveSpeed),
							   cLookAt.z + northSouth * (moveSpeed));
		vec3 newCUp = cUp;

		CameraThird::updatePosition(newCPos, newCLookAt, newCUp);
	}
}

IO::IO() {}
