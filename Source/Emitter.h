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
#include <glm/gtx/string_cast.hpp>

using namespace glm;
using namespace std;

class ModelSmoke;
class ModelBumperCar;

class Emitter {
public:
	Emitter(ModelBumperCar* parent);
	void setPosition(vec3 newPosition);
	void generateParticles();
	~Emitter();
	static const int MAX_EMITTER_PARTICLES;
private:
	static const int RATE;
	int MAX_LIFE;
	float generateRandomFloat();
	vec3 position;
	
	ModelSmoke* particleArray;
	
	void simulate();
	void draw();
	int count;
	static const vec3 EMITTER_OFFSET;
	ModelBumperCar* parent;
	int findDeadParticle();
	int pointer = 0;
	mat4* particleMatrices; //Keeps track on model matrix
	void updateParticleMatrices();
	void setupInstancedArray();
};