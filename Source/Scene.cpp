#include "Scene.h"
#include "Model.h"
#include "ModelCube.h"
#include <iostream>
#include <string>
#include <map>
#define GLEW_STATIC 1 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Scene* Scene::instance = 0;
map<string, Model*> Scene::models = {};

Scene& Scene::getInstance() {
	if(instance == 0) instance = new Scene();
	return *instance;
}

Scene::Scene() {
	Model* cube1 = new ModelCube(vec3(1.0f, 1.0f, 1.0f));
	Model* cube2 = new ModelCube(vec3(2.0f, 2.0f, 2.0f));

	cube1->SetPosition(vec3(5.0f, 0.0f, 5.0f));

	models["Cube1"] = cube1;
	models["Cube2"] = cube2;
}

void Scene::update() {

}

void Scene::draw() {

	update();

	for (auto const& model : models) {
		model.second->Draw();
	}
}


