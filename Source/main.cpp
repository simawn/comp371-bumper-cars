// Using Lab3 as an initial code template
//
// Credits:
// COMP 371 Labs Framework
// Created by Nicolas Bergeron on 20/06/2019.
//

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>

//Custom classes
#include "Shaders.h"
#include "Setup.h"
#include "IO.h"
#include "Renderer.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include <FreeImageIO.h>

using namespace glm;
using namespace std;

int main(int argc, char*argv[])
{
	Setup setup = Setup::getInstance(1600, 800, "Final");
	IO IO = IO::getInstance();
	Shaders shaders = Shaders::getInstance();
	Renderer renderer = Renderer::getInstance();


	// Camera parameters for view transform
	const vec3 START_CAM_POS(0.0f,10.0f,10.0f);
	const vec3 START_CAM_LOOKAT(0.0f, 0.0f, 0.0f);
	const vec3 START_CAM_UP(0.0f, 1.0f, 0.0f);
    vec3 cameraPosition = START_CAM_POS;
	vec3 cameraLookAt = START_CAM_LOOKAT;
	vec3 cameraUp = START_CAM_UP;

    // Set initial view matrix
	mat4 viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
    
	// Set projection matrix for shader, this won't change
	const float FOV = 70.0f;
	const float NEAR = 0.01f;
	const float FAR = 1000.0f;

    mat4 projectionMatrix = perspective(FOV, (float) setup.SCREEN_WIDTH / (float) setup.SCREEN_HEIGHT, NEAR, FAR);

	renderer.setProjectionMatrix(Shaders::currentShaderProgram, projectionMatrix);
	renderer.setViewMatrix(Shaders::currentShaderProgram, viewMatrix);

	const double MAX_FPS = 60.0;
	const double MAX_PERIOD = 1.0 / MAX_FPS;
	double lastTime = 0.0;

    // Entering Main Loop
    while(!glfwWindowShouldClose(Setup::window)) {
		double t = glfwGetTime();
		double dt = t - lastTime;

		if (dt >= MAX_PERIOD) {
			lastTime = t;

			IO.updateMousePosition();
			renderer.updateTick();
			renderer.renderScene();
			IO.processInputs();
		}
    }

    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
