#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <FreeImageIO.h>
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>

#include "Shaders.h"
#include "Setup.h"
#include "IO.h"
#include "Renderer.h"
#include "CameraThird.h"

using namespace glm;
using namespace std;

int main(int argc, char*argv[]) {
	srand(time(0));
	Setup setup = Setup::getInstance(1600, 800, "Final");
	IO IO = IO::getInstance();
	Shaders shaders = Shaders::getInstance();
	Renderer renderer = Renderer::getInstance();
	
	CameraThird cameraThird = CameraThird::getInstance(vec3(0.0f,50.0f,40.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	renderer.setProjectionMatrix(Shaders::currentShaderProgram, cameraThird.getProjMatrix());
	renderer.setProjectionMatrix(Shaders::smokeShaderProgram, cameraThird.getProjMatrix());

	const double MAX_FPS = 60.0;
	const double MAX_PERIOD = 1.0 / MAX_FPS;
	double lastTime = 0.0;

    while(!glfwWindowShouldClose(Setup::window)) {
		double t = glfwGetTime();
		double dt = t - lastTime;
		if (dt >= MAX_PERIOD) {
			lastTime = t;
			IO.updateMousePosition();
			renderer.updateTick();
			renderer.setViewMatrix(Shaders::currentShaderProgram, cameraThird.getViewMatrix());
			renderer.setViewMatrix(Shaders::smokeShaderProgram, cameraThird.getViewMatrix());
			renderer.renderScene();
			IO.processInputs();
		}
    }

    glfwTerminate();
    
	return 0;
}
