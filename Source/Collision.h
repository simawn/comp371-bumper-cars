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

class Collision {
public:
	static Collision& getInstance();
	void addObject(Model* model);
	void checkCollisions();
private:
	Collision();
	static Collision* instance;
	vector<Model*> collisionObjects;
};