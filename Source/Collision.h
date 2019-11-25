#pragma once
#include "Model.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace glm;

class Collision {
public:
	static Collision& getInstance();
	void addObject(Model* model);
	vec2 collisionCheck(Model* model);
	void debug(); //Outputs data of the first car
private:
	Collision();
	~Collision();
	static Collision* instance;
	vector<Model*> collisionObjects;
	//Debug
	static int count;
	//Returns the coords for a single moving object
	//Model pointer, topLeft, topRight, bottomLeft, bottomRight
	tuple<Model*, vec2, vec2, vec2, vec2> getCoordsFor(Model* model);
	//Calculate the unique normals
	tuple<vec2, vec2> getUniqueNormals(vec2 topLeft, vec2 topRight, vec2 bottomLeft, vec2 bottomRight);
};