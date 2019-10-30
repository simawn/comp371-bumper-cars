#include "IO.h"
#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

IO* IO::instance = 0;

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
	glfwGetCursorPos(window, &currentMousePosX, &currentMousePosY);
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

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

IO::IO() {

}
