#pragma once
#include "Model.h"
//#include "Renderer.h"

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class Movement {
public:
	static Movement& getInstance();
	void addObject(Model* model);
	void updateMovements();
private:
	Movement();
	static Movement* instance;
	vector<Model*> movingObjects;
};