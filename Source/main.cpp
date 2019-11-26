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

			if (!IO::isFirstCamera) {
				double dx = IO.getMouseMoveDifference().first;
				double dy = IO.getMouseMoveDifference().second;

				cameraThird.cameraHorizontalAngle -= dx * cameraThird.CAMERA_ANGULAR_SPEED * dt;
				cameraThird.cameraVerticalAngle   -= dy * cameraThird.CAMERA_ANGULAR_SPEED * dt;
				
				//Clamp verticle angle
				cameraThird.cameraVerticalAngle = std::max(-cameraThird.VERTICAL_CLAMP, std::min(cameraThird.VERTICAL_CLAMP, cameraThird.cameraVerticalAngle));
				
				

				if (cameraThird.cameraHorizontalAngle > 360) cameraThird.cameraHorizontalAngle -= 360;
				else if (cameraThird.cameraHorizontalAngle < -360) cameraThird.cameraHorizontalAngle += 360;

				float theta = radians(cameraThird.cameraHorizontalAngle);
				float phi = radians(cameraThird.cameraVerticalAngle);
				
				cameraThird.updatePosition(cameraThird.getPosition(), 
										   vec3(cosf(theta)*cosf(phi), sinf(phi), -sinf(theta)*cosf(phi)),
										   cameraThird.getUpVector());

				renderer.setProjectionMatrix(Shaders::currentShaderProgram, cameraThird.getProjMatrix());
				renderer.setViewMatrix(Shaders::currentShaderProgram, cameraThird.getViewMatrix());

				//cout << to_string(cameraThird.getPosition()) << endl;
				//cout << to_string(cameraThird.getLookAt()) << endl;
				//cout << to_string(cameraThird.getUpVector()) << endl << endl;
			} else {
				float cameraHeight = 3.0f;
				cameraFirst.updatePosition(	//Position                       height                            back offset
											cameraBumperCar->GetPosition() + vec3(0.0f, cameraHeight, 0.0f) + rotate(vec3(0.0f, 0.0f, 2.0f), radians(cameraBumperCar->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f)),
											//Look at
											cameraBumperCar->GetPosition() + rotate(vec3(0.0f, 0.0f, -15.0f), radians(cameraBumperCar->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f)),
											//Up
											vec3(0.0f, 1.0f, 0.0f));
				renderer.setProjectionMatrix(Shaders::currentShaderProgram, cameraFirst.getProjMatrix());
				renderer.setViewMatrix(Shaders::currentShaderProgram, cameraFirst.getViewMatrix());
			}

			renderer.renderScene();
			IO.processInputs();
		}
    }

    glfwTerminate();
    
	return 0;
}
