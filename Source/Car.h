#pragma once
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

#include <glm/gtx/string_cast.hpp> //To output matrix/vector values to string
#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h> //For rng seed
#include <vector>

using namespace glm;

//Global vars from a1.cpp
extern std::vector<GLuint> textureArray;
extern int colorShaderProgram;
extern int texturedShaderProgram;
extern float dt;
extern GLint mainColorUniformLocation;
extern GLuint worldMatrixLocation;
extern bool enableTexture;
extern bool enableShadow;

extern void setViewMatrix(int, mat4);
extern void setWorldMatrix(int, mat4);
extern void setColor(vec3, GLuint, int);
extern void useTexture(GLuint);
extern void matProperties(float, float, vec3);

class Car {
public:
	Car();
	void draw(int);
	void scaleKey(int); //Cannot be named 'scale'
	void randomPosition();
	void resetPosition();
	void renderMode(int);
	void move(int);
	~Car();
	//Spin
	float spinningAngle = 0.0f;

private:
	//World matrix location
	GLuint worldMatrixLocation;

	//Render mode
	GLenum mode = GL_TRIANGLES;

	//Offsets all components by this number from the ground
	const float WHEEL_OFFSET = 0.5f;

	//Default translation offset of the car. Used to move the car around
	vec3 posCarBody = vec3(0.0f, 1.0f + WHEEL_OFFSET, 0.0f);

	vec3 posCarBumperFront = vec3(2.5f, 0.5f + WHEEL_OFFSET, 0.0f);
	vec3 posCarBumperBack = vec3(-2.0f, 0.5f + WHEEL_OFFSET, 0.0f);
	vec3 posCarRoof = vec3(0.0f, 2.15f + WHEEL_OFFSET, 0.0f);

	vec3 posCarWheelFrontLeft = vec3(2.0f, 0.25f, 1.25f);
	vec3 posCarWheelFrontRight = vec3(2.0f, 0.25f, -1.25f);
	vec3 posCarWheelBackLeft = vec3(-1.5f, 0.25f, 1.25f);
	vec3 posCarWheelBackRight = vec3(-1.5f, 0.25f, -1.25f);

	//Rotation
	float rotCarBody = 0.0f;
	float rotCarBumperFront = 0.0f;
	float rotCarBumperBack = 0.0f;
	float rotCarRoof = 0.0f;
	float rotCarWheelFrontLeft = 0.0f; 
	float rotCarWheelFrontRight = 0.0f;
	float rotCarWheelBackLeft = 0.0f;
	float rotCarWheelBackRight = 0.0f;

	//Scale
	vec3 scaleCarBody = vec3(3.0f, 2.0f, 2.0f);
	vec3 scaleCarBumperFront = vec3(2.0f, 1.0f, 2.0f);
	vec3 scaleCarBumperBack = vec3(1.0f, 1.0f, 2.0f);
	vec3 scaleCarRoof = vec3(2.0f, 0.3f, 1.5f);
	vec3 scaleCarWheelFrontLeft = vec3(1.0f, 1.0f, 0.5f);
	vec3 scaleCarWheelFrontRight = vec3(1.0f, 1.0f, 0.5f);
	vec3 scaleCarWheelBackLeft = vec3(1.0f, 1.0f, 0.5f);
	vec3 scaleCarWheelBackRight = vec3(1.0f, 1.0f, 0.5f);

	//For car rotation
	void carRotation(float);

	//Draw single wheel
	void drawWheel(mat4, int);
};

