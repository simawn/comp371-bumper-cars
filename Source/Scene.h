#pragma once
#include "Model.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class Scene {
public:
	Scene& getInstance();
	void draw();
private:
	Scene();
	static Scene* instance;
	vector<Model> models;
};