#pragma once
#include "Model.h"

#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

class Collision {
public:
	static Collision& getInstance();
	void addObject(Model* model);
	bool IsColliding(Model* model);
private:
	Collision();
	static Collision* instance;
	vector<Model*> collisionObjects;
	//Debug
	static int count;
	//Returns the coords for a single moving object
	vector<tuple<Model*, float, float>> getCoordsFor(Model* model);
	//Returns all the currents coords of all moving object except the one passed
	vector<tuple<Model*, float, float>> getAllCoordsExcept(Model* model); 
};