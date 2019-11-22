#pragma once
#include "Shaders.h"
#include <vector>
//#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

class Light {
public:
	Light();
	Light(vec3 pos, vec3 color);
	Light(vec3 pos, vec3 color, vec3 direction);
	vec3 getPosition();
	vec3 getColor();
	vec3 getDirection();
	static bool shadowLightIsSet; //The very first point light we create will also create the shadows
	static vector<Light*> directionalLights;
	static vector<Light*> pointLights;
	static void updateLights();
protected:
	vec3 position;
	vec3 color;
	vec3 direction;
};