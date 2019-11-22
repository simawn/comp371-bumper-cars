#include "LightPoint.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
LightPoint::LightPoint(vec3 pos, vec3 color) : Light(pos, color) {
	this->position = pos;

	if (!shadowLightIsSet) {
		setShaderLocation();
		setLightMatrix();
		shadowLightIsSet = true;
	}

	pointLights.push_back(this);
}

void LightPoint::setShaderLocation() {
	glUseProgram(Shaders::currentShaderProgram);
	GLuint lightPointLocation = glGetUniformLocation(Shaders::currentShaderProgram, "lightPoint");
	glUniform3fv(lightPointLocation, 1, &position[0]);
}

void LightPoint::setLightMatrix() {
	float near_plane = 1.0f;
	float far_plane = 60.0f;
	mat4 lightProjection = perspective(90.0f, (float)Renderer::SHADOW_WIDTH / (float)Renderer::SHADOW_HEIGHT, near_plane, far_plane);
	mat4 lightView = lookAt(vec3(position.x + 0.1, position.y, position.z + 0.1), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 lightSpaceMatrix = lightProjection * lightView;

	//Set light matrix to shadow shaders
	glUseProgram(Shaders::shadowShaderProgram);
	GLuint lightSpaceMatrixLocation = glGetUniformLocation(Shaders::shadowShaderProgram, "lightSpaceMatrix");
	glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, &lightSpaceMatrix[0][0]);
	
	//Set light matrix to current shaders
	glUseProgram(Shaders::sceneShaderProgram);
	GLuint lightSpaceMatrixLocation2 = glGetUniformLocation(Shaders::sceneShaderProgram, "lightSpaceMatrix");
	glUniformMatrix4fv(lightSpaceMatrixLocation2, 1, GL_FALSE, &lightSpaceMatrix[0][0]);
}

