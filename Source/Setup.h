#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

extern GLFWwindow* window;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

class Setup {
public:
	static Setup& getInstance(int width, int height, string title);
private:
	Setup(int width, int height, string title);
	static Setup* instance;
};