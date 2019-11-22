#include "Light.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

bool Light::shadowLightIsSet = false;
vector<Light*> Light::directionalLights = {};
vector<Light*> Light::pointLights = {};

Light::Light() {}

Light::Light(vec3 pos, vec3 color) {
	this->position = pos;
	this->color = color;
}

Light::Light(vec3 pos, vec3 color, vec3 direction) {
	this->position = pos;
	this->color = color;
	this->direction = direction;
}

vec3 Light::getPosition() {
	return position;
}

vec3 Light::getColor() {
	return color;
}

vec3 Light::getDirection() {
	return direction;
}

void Light::updateLights() {
	int sceneShader = Shaders::sceneShaderProgram;

	int pointLightCount = pointLights.size();
	int dirLightCount = directionalLights.size();

	vec3* pointLightPositions = new vec3[pointLightCount];
	vec3* pointLightColors = new vec3[pointLightCount];

	vec3* dirLightPositions = new vec3[dirLightCount];
	vec3* dirLightColors = new vec3[dirLightCount];
	vec3* dirLightDirections = new vec3[dirLightCount];

	int index = 0;
	for (Light* pointLight : pointLights) {
		pointLightPositions[index] = pointLight->getPosition();
		pointLightColors[index] = pointLight->getColor();
		index++;
	}

	index = 0;
	for (Light* dirLight : directionalLights) {
		dirLightPositions[index] = dirLight->getPosition();
		dirLightColors[index] = dirLight->getColor();
		dirLightDirections[index] = dirLight->getDirection();
		index++;
	}

	for (GLuint i = 0; i < pointLightCount; i++) {
		string number = to_string(i);
		glUniform3f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].ambient").c_str()), pointLightColors[i].r * 0.1f, pointLightColors[i].g * 0.1f, pointLightColors[i].b * 0.1f);
		glUniform3f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].diffuse").c_str()), pointLightColors[i].r, pointLightColors[i].g, pointLightColors[i].b);
		glUniform3f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].linear").c_str()), 0.09f);
		glUniform1f(glGetUniformLocation(sceneShader, ("pointLights[" + number + "].quadratic").c_str()), 0.032f);
	}

	for (GLuint i = 0; i < dirLightCount; i++) {
		string number = to_string(i);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].position").c_str()), dirLightPositions[i].x, dirLightPositions[i].y, dirLightPositions[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].ambient").c_str()), dirLightColors[i].r * 0.1f, dirLightColors[i].g * 0.1f, dirLightColors[i].b * 0.1f);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].diffuse").c_str()), dirLightColors[i].r, dirLightColors[i].g, dirLightColors[i].b);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].direction").c_str()), dirLightDirections[i].x, dirLightDirections[i].y, dirLightDirections[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
	}

	delete pointLightPositions;
	delete pointLightColors;

	delete dirLightPositions;
	delete dirLightColors;
	delete dirLightDirections;
}

