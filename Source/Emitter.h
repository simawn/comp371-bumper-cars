#pragma once

#include "ModelSmoke.h"
#include "ModelBumperCar.h"

#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace glm;
using namespace std;

class ModelSmoke;
class ModelBumperCar;

class Emitter {
public:
	Emitter(ModelBumperCar* parent);
	void setPosition(vec3 newPosition);
	void generateParticles();
private:
	static const int RATE = 5;
	int MAX_LIFE;
	static const int MAX_PARTICLES = 10;
	float generateRandomFloat();
	vec3 position;
	
	vector<ModelSmoke*> particleArray;
	
	void simulate();
	void draw();
	int count;
	static const vec3 EMITTER_OFFSET;
	ModelBumperCar* parent;
};