#pragma once
#include <string>
#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class IO {
public:
	static IO& getInstance();
	void updateMousePosition();
	pair<double, double> getMouseMoveDifference();
	void processInputs();
private:
	IO();
	static IO* instance;
	pair<double, double> getCurrentMousePosition();
	pair<double, double> getLastMousePosition();
	double currentMousePosX = 0;
	double currentMousePosY = 0;
	double lastMousePosX = 0;
	double lastMousePosY = 0;
	const float CAM_SPEED = 20;
	void updateCameraPosition(int dir);
};