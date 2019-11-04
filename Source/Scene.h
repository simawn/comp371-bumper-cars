#pragma once
#include "Model.h"
#include <map>
#include <string>
//#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class Scene {
public:
	static Scene& getInstance();
	static void draw(float tick);
	
private:
	Scene();
	static Scene* instance;
	static void update(float tick);
	static map<string, Model*> models;
	static float acc;
};