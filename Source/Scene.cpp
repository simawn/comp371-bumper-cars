#include "Scene.h"

using namespace std;
using namespace glm;

Scene* Scene::instance = 0;
map<string, Model*> Scene::models = {};
float Scene::acc = 0;
Movement& Scene::movement = Movement::getInstance();

Scene& Scene::getInstance() {
	if(instance == 0) instance = new Scene();
	return *instance;
}

Scene::Scene() {
	Model* cube1 = new ModelCube(vec3(1.0f, 1.0f, 1.0f));
	Model* cube2 = new ModelCube(vec3(2.0f, 2.0f, 2.0f));
	Model* ground = new ModelCube(vec3(100.0f, 0.1f, 100.0f));
	Model* bumperCar1 = new ModelBumperCar();
	Light* lightPoint1 = new LightPoint(vec3(0.0f, 10.0f, 0.0f));

	//Controls car movements
	movement.addObject(bumperCar1);

	cube1->SetPosition(vec3(5.0f, 0.0f, 5.0f));
	cube2->SetPosition(vec3(5.0f, 0.0f, 5.0f));
	bumperCar1->SetScaling(vec3(5.0f));
	bumperCar1->SetPosition(vec3(0.0f, 0.0f, 5.0f));
	models["Cube1"] = cube1;
	models["Cube2"] = cube2;
	models["bc1"] = bumperCar1;
	models["ground"] = ground;
}

void Scene::update(float tick) {
	//Update movement
	movement.updateMovements();
}

void Scene::draw(float tick) {

	update(tick);

	for (auto const& model : models) {
		model.second->Draw();
	}
}


