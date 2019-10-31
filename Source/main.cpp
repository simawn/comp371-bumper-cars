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
#include "Car.h"
#include "Global.h"
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

std::vector<vec3> getVertexArray() {
	// Cube model
	std::vector<vec3> vertexArray = {  // position, color, uv, normal
		 vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), //left - red
		 vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),
		 vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),

		 vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),
		 vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),
		 vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f),

		 vec3(0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),// far - blue
		 vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),
		 vec3(-0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),

		 vec3(0.5f, 0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),
		 vec3(0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),
		 vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f),

		 vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f), // bottom - turquoise
		 vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),
		 vec3(0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),

		 vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),
		 vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),
		 vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f,-1.0f, 0.0f),

		 vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),// near - green
		 vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
		 vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

		 vec3(0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
		 vec3(-0.5f, 0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),
		 vec3(0.5f,-0.5f, 0.5f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f),

		 vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),// right - purple
		 vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
		 vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),

		 vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
		 vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
		 vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),

		 vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),// top - yellow
		 vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
		 vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),

		 vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
		 vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
		 vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f),
	};

	// Create cylinder object
	const int EDGES = 16.0f;
	const float RADIUS = 0.5f;
	const vec3 COLOR = vec3(0.5f, 0.5f, 0.5f);
	const float ANGLE = radians(360.0f / EDGES);
	float curAngle = 0.0f;

	//Lots of repeated vertices... to improve

	//Front
	for (int i = 0; i < EDGES; i++) {
		
		vec3 cVertex = vec3(0.0f, 0.0f, 0.5f);
		cVertex.x = RADIUS * cos(curAngle);
		cVertex.y = RADIUS * sin(curAngle);
		//Position
		vertexArray.push_back(cVertex);

		//Color
		vertexArray.push_back(COLOR);

		vec3 uvVertex = vec3(0.0f, 0.0f, 0.0f);
		uvVertex.x = 0.5f + 0.3f * cos(-curAngle);
		uvVertex.y = 0.5f + 0.3f * sin(-curAngle);
		//UV
		vertexArray.push_back(uvVertex);

		//Normal
		vertexArray.push_back(normalize(vec3(0.0f, 0.0f, 1.0f)));

		//Next it
		curAngle += ANGLE;
	}

	//Back
	for (int i = 0; i < EDGES; i++) {
		vec3 cVertex = vec3(0.0f, 0.0f, -0.5f);
		cVertex.x = RADIUS * cos(curAngle);
		cVertex.y = RADIUS * sin(curAngle);
		//Position
		vertexArray.push_back(cVertex);

		//Color
		vertexArray.push_back(COLOR);

		vec3 uvVertex = vec3(0.0f, 0.0f, 0.0f);
		uvVertex.x = 0.5f + 0.3f * cos(-curAngle);
		uvVertex.y = 0.5f + 0.3f * sin(-curAngle);
		//UV
		vertexArray.push_back(uvVertex);

		//Normal
		vertexArray.push_back(normalize(vec3(0.0f, 0.0f, -1.0f)));

		//Next it
		curAngle -= ANGLE;
	}

	float uStartL = 0.84f;
	float uStartR = 0.955f;
	float vStartL = 0.55f;
	float vStartR = 0.55f;
	//Sides
	for (int i = 0; i < EDGES + 1; i++) {

		vec3 cVertex = vec3(0.0f, 0.0f, 0.5f);

		cVertex.x = RADIUS * cos(curAngle);
		cVertex.y = RADIUS * sin(curAngle);
		//Position
		vertexArray.push_back(cVertex);

		//Colour
		vertexArray.push_back(COLOR);
		
		vStartL += 0.07;
		//UV
		vertexArray.push_back(vec3(uStartL, vStartL, 0.0f));

		//Both side share the same normal
		vec3 vNorm = normalize(vec3(cos(curAngle), sin(curAngle), 0.0f));

		//Normal
		vertexArray.push_back(vNorm);

		//Vertex for the other side

		cVertex.z = -0.5f;
		//Position
		vertexArray.push_back(cVertex);

		//Colour
		vertexArray.push_back(COLOR);

		vStartR += 0.07;
		//UV
		vertexArray.push_back(vec3(uStartR, vStartR, 0.0f));

		//Normal
		vertexArray.push_back(vNorm);

		//Next it
		curAngle += ANGLE;
	}

	return vertexArray;
}

int createVertexBufferObject()
{
	std::vector<vec3> vertexArray = getVertexArray();

    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    
    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(vec3), &vertexArray[0], GL_STATIC_DRAW); // Modified so it accepts a vector

	//POSITION
    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          4*sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
                          );
    glEnableVertexAttribArray(0);

	//COLOUR
    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(vec3),
                          (void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
                          );
    glEnableVertexAttribArray(1);

	//TEXTURE
	glVertexAttribPointer(	2,                            // attribute 2 matches aUV in Vertex Shader
							3,
							GL_FLOAT,
							GL_FALSE,
							4*sizeof(vec3),
							(void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
							);
	glEnableVertexAttribArray(2);

	//NORMAL
	glVertexAttribPointer(3,                          
		3,
		GL_FLOAT,
		GL_FALSE,
		4 * sizeof(vec3),
		(void*)(3 * sizeof(vec3))
	);
	glEnableVertexAttribArray(3);


    return vertexBufferObject;
}

void renderScene(int shaderProgram) {

	if(shaderProgram == Shaders::Shaders::shadowShaderProgram) {
		mat4 plane = translate(mat4(1.0f), vec3(0.0f, -0.1f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));
		Renderer::setWorldMatrix(shaderProgram, plane);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (shaderProgram == Shaders::Shaders::texturedShaderProgram) {
		Renderer::useTexture(Renderer::textureMap["GRASS"]);
		Renderer::matProperties(0.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
		/*
		mat4 plane = translate(mat4(1.0f), vec3(0.0f, -0.1f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));
		setWorldMatrix(shaderProgram, plane);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/
		
		for (int i = -50; i < 50; i += 5) {
			for (int j = -50; j < 50; j += 5) {
				Renderer::matProperties(0.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
				mat4 grassTiles = translate(mat4(1.0f), vec3(i, -0.1f, j)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 5.0f));
				Renderer::setWorldMatrix(shaderProgram, grassTiles);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		
		
	}

	if (shaderProgram == Shaders::Shaders::colorShaderProgram) {
		glUseProgram(Shaders::colorShaderProgram);

		Renderer::setColor(vec3(1.0f, 1.0f, 1.0f), Shaders::colorShaderProgram, 1);

		for (int i = -50; i <= 50; i++) {
			mat4 linesZ = translate(mat4(1.0f), vec3(0.0f, 0.0f, i)) * scale(mat4(1.0f), vec3(100.0f, 0.00f, 0.1f));
			Renderer::setWorldMatrix(Shaders::colorShaderProgram, linesZ);
			glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

			mat4 linesX = translate(mat4(1.0f), vec3(i, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.00f, 100.0f));
			Renderer::setWorldMatrix(Shaders::colorShaderProgram, linesX);
			glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0
		}
	}
	


	//useTexture(textureArray[4]);
	//Update car draw
	car1.draw(shaderProgram);

	glUseProgram(Shaders::colorShaderProgram);
	//Coord arrows
	Renderer::setColor(vec3(1.0f, 0.0f, 0.0f), Shaders::colorShaderProgram, 1);
	mat4 arrowX = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
	Renderer::setWorldMatrix(Shaders::colorShaderProgram, arrowX);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	Renderer::setColor(vec3(0.0f, 1.0f, 0.0f), Shaders::colorShaderProgram, 1);
	mat4 arrowY = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
	Renderer::setWorldMatrix(Shaders::colorShaderProgram, arrowY);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	Renderer::setColor(vec3(0.0f, 0.0f, 1.0f), Shaders::colorShaderProgram, 1);
	mat4 arrowZ = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
	Renderer::setWorldMatrix(Shaders::colorShaderProgram, arrowZ);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(int argc, char*argv[])
{
	Setup setup = Setup::getInstance(1600, 800, "Final");
	IO IO = IO::getInstance();
	Shaders shaders = Shaders::getInstance();
	Renderer renderer = Renderer::getInstance();

	//Mouse
	//double lastMousePosX, lastMousePosY;
	//glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

	//Keeps track of keys
	int lastSpaceState = GLFW_RELEASE;
	int lastAState = GLFW_RELEASE;
	int lastDState = GLFW_RELEASE;
	int lastXState = GLFW_RELEASE;
	int lastBState = GLFW_RELEASE;

	// Camera parameters for view transform
	const vec3 START_CAM_POS(0.0f,10.0f,10.0f);
	const vec3 START_CAM_LOOKAT(0.0f, 0.0f, 0.0f);
	const vec3 START_CAM_UP(0.0f, 1.0f, 0.0f);

	const float CAM_SPEED = 20;

    vec3 cameraPosition = START_CAM_POS;
	vec3 cameraLookAt = START_CAM_LOOKAT;
	vec3 cameraUp = START_CAM_UP;

    // Set initial view matrix
	mat4 viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
    
	// Set projection matrix for shader, this won't change
	const float FOV = 70.0f;
	const float NEAR = 0.01f;
	const float FAR = 1000.0f;

    mat4 projectionMatrix = perspective(FOV,            // field of view in degrees
                                        (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT,  // aspect ratio
                                        NEAR, FAR);   // near and far (near > 0)
	renderer.setProjectionMatrix(Shaders::colorShaderProgram, projectionMatrix);
	renderer.setProjectionMatrix(Shaders::texturedShaderProgram, projectionMatrix);

	// Define and upload geometry to the GPU here ...
	int texturedCubeVBO = createVertexBufferObject();

    // For frame time
    float lastFrameTime = glfwGetTime();
    
    
    
	//Create car obj
	//Car car1;

	//Create light
	vec3 lightPosWorld = vec3(0.0f, 30.0f, 0.0f);
	GLuint lightUniformLocation = glGetUniformLocation(Shaders::texturedShaderProgram, "lightPosWorld");
	glUniform3fv(lightUniformLocation, 1, &lightPosWorld[0]);

    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
		IO.updateMousePosition();

		//Enable shadows
		glUseProgram(Shaders::texturedShaderProgram);
		glUniform1i(glGetUniformLocation(Shaders::texturedShaderProgram, "enableShadow"), enableShadow == true? 1 : 0);

		//Update view matrix
		Renderer::setViewMatrix(Shaders::colorShaderProgram, viewMatrix);
		Renderer::setViewMatrix(Shaders::texturedShaderProgram, viewMatrix);
		

		//Fixes mouse cursor position problems
		//glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

        // Frame time calculation
		dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

		const unsigned int SHADOW_WIDTH = renderer.SHADOW_WIDTH;
		const unsigned int SHADOW_HEIGHT = renderer.SHADOW_HEIGHT;

		// 1. first render to depth map
		glCullFace(GL_FRONT);
		glUseProgram(Shaders::shadowShaderProgram);
		float near_plane = 1.0f, far_plane = 100.0f;
		mat4 lightProjection = perspective(90.0f, (float) SHADOW_WIDTH / (float) SHADOW_HEIGHT, near_plane, far_plane);
		mat4 lightView = lookAt(vec3(lightPosWorld.x + 0.1, lightPosWorld.y, lightPosWorld.z + 0.1), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		mat4 lightSpaceMatrix = lightProjection * lightView;

		GLuint lightSpaceMatrixLocation = glGetUniformLocation(Shaders::shadowShaderProgram, "lightSpaceMatrix");
		glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, renderer.depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		renderScene(Shaders::shadowShaderProgram);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glCullFace(GL_BACK);
		// 2. then render scene as normal with shadow mapping (using depth map)
		
		glUseProgram(Shaders::texturedShaderProgram);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Shadow texture in texture unit 3
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, renderer.depthMap);
		glUniform1i(glGetUniformLocation(Shaders::texturedShaderProgram, "shadowMap"), 3);

		GLuint lightSpaceMatrixLocationText = glGetUniformLocation(Shaders::texturedShaderProgram, "lightSpaceMatrix");
		glUniformMatrix4fv(lightSpaceMatrixLocationText, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		renderScene(enableTexture == true ? Shaders::texturedShaderProgram : Shaders::colorShaderProgram);
		

        glfwSwapBuffers(window);

        // Handle inputs
		IO.processInputs();
        
		//Random position
		if (lastSpaceState == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			car1.randomPosition();
		}
		lastSpaceState = glfwGetKey(window, GLFW_KEY_SPACE);

		//Toggle texture
		if (lastXState == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			enableTexture = !enableTexture;
		}
		lastXState = glfwGetKey(window, GLFW_KEY_X);

		//Toggle shadows
		if (lastBState == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			enableShadow = !enableShadow;
		}
		lastBState = glfwGetKey(window, GLFW_KEY_B);

		//Scaling
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			car1.scaleKey(0);
		}

		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			car1.scaleKey(1);
		}

		//Render modes
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			car1.renderMode(1);
		}

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			car1.renderMode(2);
		}

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			car1.renderMode(3);
		}
		
		//Moving car
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			car1.move(0);
			car1.spinningAngle += 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			car1.move(1);
			car1.spinningAngle -= 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				car1.move(2);
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				car1.move(3);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				car1.move(3);
			}
			else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				car1.move(2);
			}
		}

		//Moving world
		//Commented out vars are intuitive transformations based on the arrow keys
		//The requirements in the assignment seems to be different
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			//viewMatrix *= rotate(mat4(1.0f), radians(0.1f), vec3(1.0f, 0.0f, 0.0f));
			viewMatrix *= rotate(mat4(1.0f), radians(0.1f), vec3(0.0f, 1.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			//viewMatrix *= rotate(mat4(1.0f), radians(-0.1f), vec3(1.0f, 0.0f, 0.0f));
			viewMatrix *= rotate(mat4(1.0f), radians(-0.1f), vec3(0.0f, 1.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			//viewMatrix *= rotate(mat4(1.0f), radians(-0.1f), vec3(0.0f, 0.0f, 1.0f));
			viewMatrix *= rotate(mat4(1.0f), radians(0.1f), vec3(1.0f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			//viewMatrix *= rotate(mat4(1.0f), radians(0.1f), vec3(0.0f, 0.0f, 1.0f));
			viewMatrix *= rotate(mat4(1.0f), radians(-0.1f), vec3(1.0f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) { //Reset
			viewMatrix = lookAt(START_CAM_POS, START_CAM_LOOKAT, START_CAM_UP);
			car1.resetPosition();
		}

		//Zoom in out
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			//double mousePosX, mousePosY;
			//glfwGetCursorPos(window, &mousePosX, &mousePosY);

			//double dy = mousePosY - lastMousePosY;
			double dy = IO.getMouseMoveDifference().second;

			viewMatrix *= scale(mat4(1.0f), vec3(1.0f + (dy * dt)));

			//Below preserves camera params
			//cameraPosition *= vec3(1.0f + (dy * dt));
			//cameraLookAt *= vec3(1.0f + (dy * dt));
			//cameraUp *= vec3(1.0f + (dy * dt));
			//viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
		}

		//Pan
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			//double mousePosX, mousePosY;
			//glfwGetCursorPos(window, &mousePosX, &mousePosY);

			//float dx = mousePosX - lastMousePosX;
			float dx = IO.getMouseMoveDifference().first;

			cameraLookAt.x += dx * dt * CAM_SPEED;

			//viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
			viewMatrix *= rotate(mat4(1.0f), radians(dx), vec3(0.0f, 1.0f, 0.0f));
		}

		//Tilt
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			//double mousePosX, mousePosY;
			//glfwGetCursorPos(window, &mousePosX, &mousePosY);

			//double dy = mousePosY - lastMousePosY;

			double dy = IO.getMouseMoveDifference().second;
			cameraLookAt.y -= dy * dt * CAM_SPEED;

			viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
		}

		
    }

    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
