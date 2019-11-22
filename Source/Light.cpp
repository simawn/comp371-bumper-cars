#include "Light.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

bool Light::shadowLightIsSet = false;
vector<Light*> Light::directionalLights = {};
vector<Light*> Light::pointLights = {};
vector<Light*> Light::spotLights = {};

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

Light::Light(vec3 pos, vec3 color, vec3 direction, float cutOff, float outerCutOff) {
	this->position = pos;
	this->color = color;
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
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

float Light::getCutOff() {
	return cutOff;
}

float Light::getOuterCutOff() {
	return outerCutOff;
}

void Light::setPosition(vec3 pos) {
	this->position = pos;
}

void Light::setDirection(vec3 dir) {
	this->direction = dir;
}

void Light::setColor(vec3 color) {
	this->color = color;
}

void Light::updateLights() {
	int sceneShader = Shaders::sceneShaderProgram;

	int pointLightCount = pointLights.size();
	int dirLightCount = directionalLights.size();
	int spotLightCount = spotLights.size();

	vec3* pointLightPositions = new vec3[pointLightCount];
	vec3* pointLightColors = new vec3[pointLightCount];

	//vec3* dirLightPositions = new vec3[dirLightCount];
	vec3* dirLightColors = new vec3[dirLightCount];
	vec3* dirLightDirections = new vec3[dirLightCount];

	vec3* spotLightPositions = new vec3[spotLightCount];
	vec3* spotLightColors = new vec3[spotLightCount];
	vec3* spotLightDirections = new vec3[spotLightCount];
	float* spotLightCutOff = new float[spotLightCount];
	float* spotLightOuterCutOff = new float[spotLightCount];

	int index = 0;
	for (Light* pointLight : pointLights) {
		pointLightPositions[index] = pointLight->getPosition();
		pointLightColors[index] = pointLight->getColor();
		index++;
	}

	index = 0;
	for (Light* dirLight : directionalLights) {
		dirLightColors[index] = dirLight->getColor();
		dirLightDirections[index] = dirLight->getDirection();
		index++;
	}

	index = 0;
	for (Light* spotLight : spotLights) {
		spotLightPositions[index] = spotLight->getPosition();
		spotLightColors[index] = spotLight->getColor();
		spotLightDirections[index] = spotLight->getDirection();
		spotLightCutOff[index] = spotLight->getCutOff();
		spotLightOuterCutOff[index] = spotLight->getOuterCutOff();
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
		//glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].position").c_str()), dirLightPositions[i].x, dirLightPositions[i].y, dirLightPositions[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].ambient").c_str()), dirLightColors[i].r * 0.1f, dirLightColors[i].g * 0.1f, dirLightColors[i].b * 0.1f);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].diffuse").c_str()), dirLightColors[i].r, dirLightColors[i].g, dirLightColors[i].b);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].direction").c_str()), dirLightDirections[i].x, dirLightDirections[i].y, dirLightDirections[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("dirLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
	}

	for (GLuint i = 0; i < spotLightCount; i++) {
		string number = to_string(i);
		glUniform3f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].position").c_str()), spotLightPositions[i].x, spotLightPositions[i].y, spotLightPositions[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].ambient").c_str()), spotLightColors[i].r * 0.1f, spotLightColors[i].g * 0.1f, spotLightColors[i].b * 0.1f);
		glUniform3f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].diffuse").c_str()), spotLightColors[i].r, spotLightColors[i].g, spotLightColors[i].b);
		glUniform3f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].direction").c_str()), spotLightDirections[i].x, spotLightDirections[i].y, spotLightDirections[i].z);
		glUniform3f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].linear").c_str()), 0.09f);
		glUniform1f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].quadratic").c_str()), 0.032f);
		glUniform1f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].cutOff").c_str()), spotLightCutOff[i]);
		glUniform1f(glGetUniformLocation(sceneShader, ("spotLights[" + number + "].outerCutOff").c_str()), spotLightOuterCutOff[i]);
	}

	delete pointLightPositions;
	delete pointLightColors;

	//delete dirLightPositions;
	delete dirLightColors;
	delete dirLightDirections;

	delete spotLightPositions;
	delete spotLightColors;
	delete spotLightDirections;
	delete spotLightCutOff;
	delete spotLightOuterCutOff;
}
