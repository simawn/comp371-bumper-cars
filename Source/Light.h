#pragma once
#include "Shaders.h"
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
	Light(vec3 pos);
	vec3 getPosition();
	virtual void setPosition(vec3 pos) = 0;
protected:
	vec3 position;
	virtual void setShaderLocation() = 0;
	
};