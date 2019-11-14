#pragma once

#include "Model.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class ModelBumperCar : public Model
{
public:
	ModelBumperCar();
	virtual ~ModelBumperCar();

	virtual void Update(float dt);
	virtual void Draw();

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
};
