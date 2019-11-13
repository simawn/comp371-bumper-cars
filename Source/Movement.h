#pragma once
#include "Model.h"
#include <time.h>
//#include "Renderer.h"

#include <vector>
#include <map>
#include <array>
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
	//Stores movement properties of the moving objects
	map<Model*, float[6]> movingObjects;
	//float[3]
	//[0] stores a random int that defines the behaviour of the object
	//[1] ideal max step size for foward movement
	//[2] stores the current step count for foward movement
	//[3] ideal max step size for rotating movement
	//[4] stores the current step count for rotating movement
	//[5] stores the current state of the obj
		//0: can move
		//1: stuck
	float generateRandomFloat(); //Between 0 and 1
};