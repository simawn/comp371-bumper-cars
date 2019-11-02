#include "Scene.h"
#include "Model.h"
#include "ModelCube.h"
#include <iostream>
#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Scene* Scene::instance = 0;
vector<Model*> Scene::models = {};

Scene& Scene::getInstance() {
	if(instance == 0) instance = new Scene();
	return *instance;
}

Scene::Scene() {
	Model* cube = new ModelCube(vec3(1.0f, 1.0f, 1.0f));
	models.push_back(cube);
}

void Scene::draw() {
	for (Model* model : models) {
		model->Draw();
	}
}
