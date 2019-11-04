#pragma once
#include <string>
//#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class Setup {
public:
	static Setup& getInstance(int width, int height, string title);
	static GLFWwindow* window;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
private:
	Setup(int width, int height, string title);
	static Setup* instance;
};