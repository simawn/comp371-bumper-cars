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
	//Model* cube1 = new ModelCube(vec3(1.0f, 1.0f, 1.0f));
	//Model* cube2 = new ModelCube(vec3(2.0f, 2.0f, 2.0f));
	//Model* smoke = new ModelSmoke();
	Model* ground = new ModelCube(vec3(50.0f, 0.1f, 50.0f));
	//Model* ground = new ModelCube(vec3(5.0f, 1.0f, 7.5f)); //reference for a single car
	Model* bumperCar1 = new ModelBumperCar();
	Model* bumperCar2 = new ModelBumperCar();
	Model* bumperCar3 = new ModelBumperCar();
	Model* bumperCar4 = new ModelBumperCar();
	Model* bumperCar5 = new ModelBumperCar();
	Light* lightPoint1 = new LightPoint(vec3(5.0f, 25.0f, -9.0f));

	//Controls car movements
	//movement.addObject(bumperCar1);
	movement.addObject(bumperCar2);
	movement.addObject(bumperCar3);
	movement.addObject(bumperCar4);
	movement.addObject(bumperCar5);

	//cube1->SetPosition(vec3(5.0f, 0.0f, 5.0f));
	//cube2->SetPosition(vec3(5.0f, 0.0f, 5.0f));
	//smoke->SetScaling(vec3(50.0f));
	bumperCar1->SetScaling(vec3(5.0f));
	bumperCar2->SetScaling(vec3(5.0f));
	bumperCar3->SetScaling(vec3(5.0f));
	bumperCar4->SetScaling(vec3(5.0f));
	bumperCar5->SetScaling(vec3(5.0f));

	//smoke->SetPosition(vec3(0.0f, 3.0f, 0.0f));
	bumperCar1->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	bumperCar2->SetPosition(vec3(-10.0f, 0.0f, -10.0f));
	bumperCar3->SetPosition(vec3(-5.0f, 0.0f, -5.0f));
	bumperCar4->SetPosition(vec3(0.0f, 0.0f, 10.0f));
	bumperCar5->SetPosition(vec3(5.0f, 0.0f, 5.0f));

	bumperCar1->SetRotation(bumperCar1->GetRotationAxis(), 180);
	bumperCar2->SetRotation(bumperCar2->GetRotationAxis(), 45);
	bumperCar3->SetRotation(bumperCar3->GetRotationAxis(), 90);
	bumperCar4->SetRotation(bumperCar4->GetRotationAxis(), 75);

	//models["Cube1"] = cube1;
	//models["Cube2"] = cube2;
	//models["smoke1"] = smoke;
	models["bc1"] = bumperCar1;
	models["bc2"] = bumperCar2;
	models["bc3"] = bumperCar3;
	models["bc4"] = bumperCar4;
	models["bc5"] = bumperCar5;
	models["ground"] = ground;
}

void Scene::update(float tick) {
	//Update movement
	movement.updateMovements();
	models["bc1"]->SetRotation(vec3(0.0f, 1.0f, 0.0f), models["bc1"]->GetRotationAngle() + tick * 40);
}

void Scene::draw(float tick) {

	update(tick);

	for (auto const& model : models) {
		model.second->Draw();
	}
}


