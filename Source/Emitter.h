#pragma once

#include "ModelSmoke.h"

#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

class Emitter {
public:
	Emitter();
	void setPosition(vec3 newPosition);
	void generateParticles();
private:
	static const int RATE = 10;
	static const int MAX_LIFE = 120;

	vec3 position;
	static const int MAX_PARTICLES;
	vector<Model*> particleArray;
	
	void simulate();
	void draw();
	int count;
};