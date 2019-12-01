#pragma once
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

class IO {
public:
	static IO& getInstance();
	void updateMousePosition();
	static pair<double, double> getMouseMoveDifference();
	static pair<double, double> getCurrentMousePosition();
	static pair<double, double> getLastMousePosition();
	void processInputs();
	static bool stopSimulation;
	static bool stopLights;
	static bool isFirstCamera;
private:
	IO();
	static IO* instance;
	static double currentMousePosX;
	static double currentMousePosY;
	static double lastMousePosX;
	static double lastMousePosY;
	const float CAM_SPEED = 20;
	void updateCameraPosition(int dir);
	//Keep track of keys
	int lastHState = GLFW_RELEASE;
	int lastLState = GLFW_RELEASE;
	int lastCState = GLFW_RELEASE;
};