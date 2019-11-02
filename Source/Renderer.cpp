#include "Renderer.h"
#include "Shaders.h"
#include "Scene.h"
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <FreeImage.h>

using namespace std;
using namespace glm;

//Static vars init
Renderer* Renderer::instance = 0;
map<string, GLuint> Renderer::textureMap = {};
unsigned int Renderer::depthMap = 0;
unsigned int Renderer::depthMapFBO = 0;

Renderer& Renderer::getInstance() {
	if (instance == 0) instance = new Renderer();
	return *instance;
}

Renderer::Renderer() {
	//createDepthMap(); messes initial render
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	setTexture();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//Generate Scene
	Scene::getInstance();
}

void Renderer::renderScene() {
	Scene::draw();
}

void Renderer::createDepthMap() {
	//Depth map. Modified code from: https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
	//Create frame buffer to store texture
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

	//Actual depth map texture
	
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
}

void Renderer::setTexture() {
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
	
	textureMap["BRICK"] = brickTextureID;
	textureMap["CEMENT"] = cementTextureID;
	textureMap["TIRE"] = tiresTextureID;
	textureMap["GRASS"] = grassTextureID;
	textureMap["RED"] = redTextureID;
}

int Renderer::loadTexture(char* imagepath) {
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

void Renderer::setProjectionMatrix(int shaderProgram, mat4 projectionMatrix) {
	glUseProgram(shaderProgram);
	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Renderer::setViewMatrix(int shaderProgram, mat4 viewMatrix) {
	glUseProgram(shaderProgram);
	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Renderer::setWorldMatrix(int shaderProgram, mat4 worldMatrix) {
	glUseProgram(shaderProgram);
	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

void Renderer::useTexture(GLuint textureID) {
	glUseProgram(Shaders::currentShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(Shaders::currentShaderProgram, "textureSampler");
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureLocation, 0);
}

void Renderer::setColor(vec3 mainColor, GLuint location, int useColor) {
	GLint mainColorUniformLocation = glGetUniformLocation(location, "mainColor");
	glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);

	GLuint useColorUniformLocation = glGetUniformLocation(location, "useColor");
	glUniform1i(useColorUniformLocation, useColor);
}

void Renderer::matProperties(float specStrength, float specHighlight, vec3 matSpecColor) {
	GLuint specStrengthUniformLocation = glGetUniformLocation(Shaders::currentShaderProgram, "specStrength");
	glUniform1f(specStrengthUniformLocation, specStrength);

	GLuint specHighlightUniformLocation = glGetUniformLocation(Shaders::currentShaderProgram, "specHighlight");
	glUniform1f(specHighlightUniformLocation, specHighlight);

	GLuint specColorUniformLocation = glGetUniformLocation(Shaders::currentShaderProgram, "matSpecColor");
	glUniform3fv(specColorUniformLocation, 1, &matSpecColor[0]);
}