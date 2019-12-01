#pragma once
#include "LightPoint.h"
#include "LightDirectional.h"
#include "LightSpot.h"
#include "Model.h"
#include "ModelCube.h"
#include "ModelBumperCar.h"
#include "ModelSmoke.h"
#include "ModelField.h"
#include "Movement.h"
#include "Emitter.h"
#include "IO.h"

#include <map>
#include <string>
#include <iostream>
//#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class Emitter;

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
	static Movement& movement;
	static void generateCars(int num);
};