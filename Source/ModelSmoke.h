#pragma once

#include "Model.h"
#include "Renderer.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

class ModelSmoke : public Model {
public:
	ModelSmoke();
	virtual ~ModelSmoke();

	virtual void Update(float dt);
	virtual void Draw();
	int life;
	float size;
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

	int smokeVertices;
	GLuint smokeVAO;
	static vector<objl::Mesh> obj;
};