#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;
class Model {
public:
	Model();
	void draw();
private:
	vec3 position;
	vec3 scale;
	vec3 rotation;
};