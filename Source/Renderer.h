#pragma once
#include "Shaders.h"
#include "Scene.h"
#include <string>
#include <map>
//#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <FreeImage.h>

using namespace std;
using namespace glm;

class Renderer {
public:
	static Renderer& getInstance();
	static map<string, GLuint> textureMap;
	static unsigned int depthMap;
	static unsigned int depthMapFBO;
	static const unsigned int SHADOW_WIDTH = 4096;
	static const unsigned int SHADOW_HEIGHT = 4096;
	static void setProjectionMatrix(int shaderProgram, mat4 projectionMatrix);
	static void setViewMatrix(int shaderProgram, mat4 viewMatrix);
	static void setWorldMatrix(int shaderProgram, mat4 worldMatrix);

	static void useTexture(GLuint textureID);

	static void setDiffuseColor(vec3 mainColor);

	static void matProperties(float specStrength, float specHighlight, vec3 matSpecColor);

	static float tick;
	void updateTick();
	void renderScene();
private:
	static Renderer* instance;
	Renderer();
	void createDepthMap();
	void setTexture();
	int loadTexture(char * imagepath);
	float lastFrameTime;
};