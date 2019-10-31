//Contains global variables used across the program

#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include "Car.h"

//std::vector<GLuint> textureArray;
//int colorShaderProgram;
//int texturedShaderProgram;
//int shadowShaderProgram;
float dt;
//GLint mainColorUniformLocation;
//GLuint worldMatrixLocation;
bool enableTexture = true;
bool enableShadow = true;
Car car1;
//unsigned int depthMap;
GLFWwindow* window;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;