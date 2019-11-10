#include "LightPoint.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
LightPoint::LightPoint(vec3 pos) : Light(pos) {
	setPosition(pos);
}

void LightPoint::setPosition(vec3 pos) {
	position = pos;
	setShaderLocation();
}

void LightPoint::setShaderLocation() {
	glUseProgram(Shaders::currentShaderProgram);
	GLuint lightPointLocation = glGetUniformLocation(Shaders::currentShaderProgram, "lightPoint");
	glUniform3fv(lightPointLocation, GL_FALSE, &position[0]);
	std::cout << "In setShaderLocation " << lightPointLocation << ": " << to_string(position) << endl;
}

