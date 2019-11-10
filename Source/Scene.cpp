#include "Scene.h"

using namespace std;
using namespace glm;

Scene* Scene::instance = 0;
map<string, Model*> Scene::models = {};
float Scene::acc = 0;

Scene& Scene::getInstance() {
	if(instance == 0) instance = new Scene();
	return *instance;
}

Scene::Scene() {
	Model* cube1 = new ModelCube(vec3(1.0f, 1.0f, 1.0f));
	Model* cube2 = new ModelCube(vec3(2.0f, 2.0f, 2.0f));
	Model* ground = new ModelCube(vec3(100.0f, 0.1f, 100.0f));
	Model* bumperCar1 = new ModelBumperCar();
	Light* lightPoint1 = new LightPoint(vec3(10.1f, 100.0f, 0.1f));
	
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
	//cout << tick << endl;
	Model* cube1 = models["Cube1"];
	cube1->SetPosition(cube1->GetPosition() + vec3(tick));

	Model* bc1 = models["bc1"];
	bc1->SetRotation(vec3(0.0f, 1.0f, 0.0f), acc * 100);
	acc += tick;
}

void Scene::draw(float tick) {

	update(tick);

	for (auto const& model : models) {
		model.second->Draw();
	}
}


