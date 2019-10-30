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

void setProjectionMatrix(int shaderProgram, mat4 projectionMatrix) {
	glUseProgram(shaderProgram);
	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void setViewMatrix(int shaderProgram, mat4 viewMatrix) {
	glUseProgram(shaderProgram);
	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void setWorldMatrix(int shaderProgram, mat4 worldMatrix) {
	glUseProgram(shaderProgram);
	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

void setColor(vec3 mainColor, GLuint location, int useColor) {
	mainColorUniformLocation = glGetUniformLocation(location, "mainColor");
	glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);

	GLuint useColorUniformLocation = glGetUniformLocation(location, "useColor");
	glUniform1i(useColorUniformLocation, useColor);
}

void matProperties(float specStrength, float specHighlight, vec3 matSpecColor) {
	GLuint specStrengthUniformLocation = glGetUniformLocation(texturedShaderProgram, "specStrength");
	glUniform1f(specStrengthUniformLocation, specStrength);

	GLuint specHighlightUniformLocation = glGetUniformLocation(texturedShaderProgram, "specHighlight");
	glUniform1f(specHighlightUniformLocation, specHighlight);

	GLuint specColorUniformLocation = glGetUniformLocation(texturedShaderProgram, "matSpecColor");
	glUniform3fv(specColorUniformLocation, 1, &matSpecColor[0]);
}

void useTexture(GLuint textureID) {
	glUseProgram(texturedShaderProgram);
	glActiveTexture(GL_TEXTURE0); //TODO
	GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureLocation, 0);
}

int loadTexture(char* imagepath) {
	// Load image using the Free Image library
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagepath, 0);
	FIBITMAP* image = FreeImage_Load(format, imagepath);
	FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
	// Get an available texture index from OpenGL
	GLuint texture = 0;
	glGenTextures(1, &texture);
	assert(texture != 0);

	// Set OpenGL filtering properties (bi-linear interpolation)
	//Model not necessarily 1024x1024. Texture needs to either scale up or down depending on zoom level
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Retrieve width and hight
	int width = FreeImage_GetWidth(image32bits);
	int height = FreeImage_GetHeight(image32bits);

	// This will upload the texture to the GPU memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

	// Free images. removes img
	FreeImage_Unload(image);
	FreeImage_Unload(image32bits);

	return texture;
}

void renderScene(int shaderProgram) {

	if(shaderProgram == shadowShaderProgram) {
		mat4 plane = translate(mat4(1.0f), vec3(0.0f, -0.1f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));
		setWorldMatrix(shaderProgram, plane);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	if (shaderProgram == texturedShaderProgram) {
		useTexture(textureArray[3]);
		matProperties(0.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
		/*
		mat4 plane = translate(mat4(1.0f), vec3(0.0f, -0.1f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));
		setWorldMatrix(shaderProgram, plane);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/
		
		for (int i = -50; i < 50; i += 5) {
			for (int j = -50; j < 50; j += 5) {
				matProperties(0.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
				mat4 grassTiles = translate(mat4(1.0f), vec3(i, -0.1f, j)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 5.0f));
				setWorldMatrix(shaderProgram, grassTiles);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		
		
	}

	if (shaderProgram == colorShaderProgram) {
		glUseProgram(colorShaderProgram);

		setColor(vec3(1.0f, 1.0f, 1.0f), colorShaderProgram, 1);

		for (int i = -50; i <= 50; i++) {
			mat4 linesZ = translate(mat4(1.0f), vec3(0.0f, 0.0f, i)) * scale(mat4(1.0f), vec3(100.0f, 0.00f, 0.1f));
			setWorldMatrix(colorShaderProgram, linesZ);
			glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

			mat4 linesX = translate(mat4(1.0f), vec3(i, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.00f, 100.0f));
			setWorldMatrix(colorShaderProgram, linesX);
			glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0
		}
	}
	


	//useTexture(textureArray[4]);
	//Update car draw
	car1.draw(shaderProgram);

	glUseProgram(colorShaderProgram);
	//Coord arrows
	setColor(vec3(1.0f, 0.0f, 0.0f), colorShaderProgram, 1);
	mat4 arrowX = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
	setWorldMatrix(colorShaderProgram, arrowX);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	setColor(vec3(0.0f, 1.0f, 0.0f), colorShaderProgram, 1);
	mat4 arrowY = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
	setWorldMatrix(colorShaderProgram, arrowY);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	setColor(vec3(0.0f, 0.0f, 1.0f), colorShaderProgram, 1);
	mat4 arrowZ = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
	setWorldMatrix(colorShaderProgram, arrowZ);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(int argc, char*argv[])
{
	Setup setup = Setup::getInstance(1920, 1080, "Final");

	//Mouse
	double lastMousePosX, lastMousePosY;
	glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

	//Keeps track of keys
	int lastSpaceState = GLFW_RELEASE;
	int lastAState = GLFW_RELEASE;
	int lastDState = GLFW_RELEASE;
	int lastXState = GLFW_RELEASE;
	int lastBState = GLFW_RELEASE;

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

	// Load Textures
#if defined(PLATFORM_OSX)
	GLuint brickTextureID = loadTexture("Textures/brick.jpg");
	GLuint cementTextureID = loadTexture("Textures/cement.jpg");
	GLuint tiresTextureID = loadTexture("Textures/tires.jpg");
	GLuint grassTextureID = loadTexture("Textures/grass512.jpg");
	GLuint redTextureID = loadTexture("Textures/red.jpg");
#else
	GLuint brickTextureID = loadTexture("../Assets/Textures/brick.jpg");
	GLuint cementTextureID = loadTexture("../Assets/Textures/cement.jpg");
	GLuint tiresTextureID = loadTexture("../Assets/Textures/tires.jpg");
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass512.jpg");
	GLuint redTextureID = loadTexture("../Assets/Textures/red.jpg");
#endif

	//Use enums instead?
	textureArray.push_back(brickTextureID);
	textureArray.push_back(cementTextureID);
	textureArray.push_back(tiresTextureID);
	textureArray.push_back(grassTextureID);
	textureArray.push_back(redTextureID);

    // Black background
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    // Compile and link shaders here ...
	Shaders shaders = Shaders::getInstance();

    
    
    //GLuint projectionMatrixLocation = glGetUniformLocation(colorShaderProgram, "projectionMatrix");
    //glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

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
    
	// Set View and Projection matrices on both shaders
	//setViewMatrix(colorShaderProgram, viewMatrix);
	//setViewMatrix(texturedShaderProgram, viewMatrix);
// Set projection matrix for shader, this won't change
	const float FOV = 70.0f;
	const float NEAR = 0.01f;
	const float FAR = 1000.0f;

    mat4 projectionMatrix = perspective(FOV,            // field of view in degrees
                                        (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT,  // aspect ratio
                                        NEAR, FAR);   // near and far (near > 0)
	setProjectionMatrix(colorShaderProgram, projectionMatrix);
	setProjectionMatrix(texturedShaderProgram, projectionMatrix);

	// Define and upload geometry to the GPU here ...
	int texturedCubeVBO = createVertexBufferObject();

    // For frame time
    float lastFrameTime = glfwGetTime();
    
    
    
	//Create car obj
	//Car car1;

	//Create light
	vec3 lightPosWorld = vec3(0.0f, 30.0f, 0.0f);
	GLuint lightUniformLocation = glGetUniformLocation(texturedShaderProgram, "lightPosWorld");
	glUniform3fv(lightUniformLocation, 1, &lightPosWorld[0]);

	//Depth map. Modified code from: https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
	//Create frame buffer to store texture
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	//Actual depth map texture
	const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
	//unsigned int depthMap;
	glGenTextures(1, &depthMap);

	//Texture operations will affect this
	glBindTexture(GL_TEXTURE_2D, depthMap);

	//Give empty img to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	
	//Params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return 0;

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	
	//Used to overwrite the initial colors that are set in the vertex array
	//vec3 mainColor(1.0f, 1.0f, 1.0f); //Default to white
	//mainColorUniformLocation = glGetUniformLocation(colorShaderProgram, "mainColor");

	// Draw geometry
	//glBindBuffer(GL_ARRAY_BUFFER, texturedCubeVBO);

	//worldMatrixLocation = glGetUniformLocation(colorShaderProgram, "worldMatrix");

	// Other OpenGL states to set once
	// Enable Backface culling
	glEnable(GL_CULL_FACE);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
		//Enable shadows
		glUseProgram(texturedShaderProgram);
		glUniform1i(glGetUniformLocation(texturedShaderProgram, "enableShadow"), enableShadow == true? 1 : 0);

		//Update view matrix
		setViewMatrix(colorShaderProgram, viewMatrix);
		setViewMatrix(texturedShaderProgram, viewMatrix);
		

		//Fixes mouse cursor position problems
		glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

        // Frame time calculation
		dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

		// 1. first render to depth map
		glCullFace(GL_FRONT);
		glUseProgram(shadowShaderProgram);
		float near_plane = 1.0f, far_plane = 100.0f;
		mat4 lightProjection = perspective(90.0f, (float) SHADOW_WIDTH / (float) SHADOW_HEIGHT, near_plane, far_plane);
		mat4 lightView = lookAt(vec3(lightPosWorld.x + 0.1, lightPosWorld.y, lightPosWorld.z + 0.1), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		mat4 lightSpaceMatrix = lightProjection * lightView;

		GLuint lightSpaceMatrixLocation = glGetUniformLocation(shadowShaderProgram, "lightSpaceMatrix");
		glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		renderScene(shadowShaderProgram);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glCullFace(GL_BACK);
		// 2. then render scene as normal with shadow mapping (using depth map)
		
		glUseProgram(texturedShaderProgram);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Shadow texture in texture unit 3
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glUniform1i(glGetUniformLocation(texturedShaderProgram, "shadowMap"), 3);

		GLuint lightSpaceMatrixLocationText = glGetUniformLocation(texturedShaderProgram, "lightSpaceMatrix");
		glUniformMatrix4fv(lightSpaceMatrixLocationText, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

		renderScene(enableTexture == true ? texturedShaderProgram : colorShaderProgram);
		

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
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
			double mousePosX, mousePosY;
			glfwGetCursorPos(window, &mousePosX, &mousePosY);

			double dy = mousePosY - lastMousePosY;

			viewMatrix *= scale(mat4(1.0f), vec3(1.0f + (dy * dt)));

			//Below preserves camera params
			//cameraPosition *= vec3(1.0f + (dy * dt));
			//cameraLookAt *= vec3(1.0f + (dy * dt));
			//cameraUp *= vec3(1.0f + (dy * dt));
			//viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
		}

		//Pan
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			double mousePosX, mousePosY;
			glfwGetCursorPos(window, &mousePosX, &mousePosY);

			float dx = mousePosX - lastMousePosX;

			cameraLookAt.x += dx * dt * CAM_SPEED;

			//viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
			viewMatrix *= rotate(mat4(1.0f), radians(dx), vec3(0.0f, 1.0f, 0.0f));
		}

		//Tilt
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			double mousePosX, mousePosY;
			glfwGetCursorPos(window, &mousePosX, &mousePosY);

			double dy = mousePosY - lastMousePosY;

			cameraLookAt.y -= dy * dt * CAM_SPEED;

			viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
		}

		
    }

    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}
