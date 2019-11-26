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
	pair<double, double> getCurrentMousePosition();
	pair<double, double> getLastMousePosition();
	void processInputs();
	static bool stopSimulation;
	static bool stopLights;
	static bool isFirstCamera;
private:
	IO();
	static IO* instance;
	double currentMousePosX = 0;
	double currentMousePosY = 0;
	double lastMousePosX = 0;
	double lastMousePosY = 0;
	const float CAM_SPEED = 20;
	void updateCameraPosition(int dir);
	//Keep track of keys
	int lastHState = GLFW_RELEASE;
	int lastLState = GLFW_RELEASE;
	int lastCState = GLFW_RELEASE;
};