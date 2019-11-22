#pragma once

#include "LightSpot.h"
#include "Emitter.h"
#include "Model.h"
#include "IO.h"

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

class Emitter;

class ModelBumperCar : public Model
{
public:
	ModelBumperCar();
	virtual ~ModelBumperCar();

	virtual void Update(float dt);
	virtual void Draw();

	static vector<ModelBumperCar*> bumperCarList;

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	unsigned int mVAO;
	unsigned int mVBO;

	int bumperCarVertices;
	GLuint bumperCarVAO;
	vec3 diffuseColor;
	static vector<objl::Mesh> obj;
	Emitter* emitter;
	LightSpot* lights[4];
	vec3 lightPosOffsets[4];
	vec3 lightDirOffsets[4];
	vec3 lightColors[4];
};
