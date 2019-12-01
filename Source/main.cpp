#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/common.hpp>
#include <FreeImageIO.h>
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Shaders.h"
#include "Setup.h"
#include "IO.h"
#include "Renderer.h"
#include "CameraThird.h"
#include "CameraFirst.h"

using namespace glm;
using namespace std;

int main(int argc, char*argv[]) {
	srand(time(0));
	Setup setup = Setup::getInstance(1920, 1080, "Bumper Cars");
	IO IO = IO::getInstance();
	Shaders shaders = Shaders::getInstance();
	Renderer renderer = Renderer::getInstance();
	
	CameraThird cameraThird = CameraThird::getInstance(vec3(0, 50, 40), vec3(0,0,0), vec3(0.0f, 1.0f, 0.0f));
	CameraFirst cameraFirst = CameraFirst::getInstance(vec3(0.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));

	//Bumper car where the first person camera will follow
	ModelBumperCar* cameraBumperCar = ModelBumperCar::bumperCarList.back();
	
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

			mat4 projMatrix;
			mat4 viewMatrix;

			if (!IO::isFirstCamera) {
				cameraThird.updateInput();
				projMatrix = cameraThird.getProjMatrix();
				viewMatrix = cameraThird.getViewMatrix();
			} else {
				cameraFirst.updateInput(cameraBumperCar);
				projMatrix = cameraFirst.getProjMatrix();
				viewMatrix = cameraFirst.getViewMatrix();
			}

			renderer.setProjectionMatrix(Shaders::currentShaderProgram, projMatrix);
			renderer.setViewMatrix(Shaders::currentShaderProgram, viewMatrix);

			renderer.renderScene();
			IO.processInputs();
		}
    }

    glfwTerminate();
    
	return 0;
}
