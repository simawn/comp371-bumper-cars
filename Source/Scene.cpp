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
	//References for car light positioning
	//Model* cube1 = new ModelCube(vec3(0.1f, 0.1f, 0.1f));
	//cube1->SetPosition(vec3(0.85f, 2.2f, 3.3f)); //position right back light
	//cube1->SetPosition(vec3(-0.85f, 2.2f, 3.3f)); //position left back light
	//cube1->SetPosition(vec3(-1.05f, 1.15f, -3.3f)); //position left front light
	//cube1->SetPosition(vec3(1.05f, 1.15f, -3.3f)); //position right front light

	Model* ground = new ModelCube(vec3(50.0f, 0.1f, 50.0f));

	generateCars(5); //Need to update frag shader with proper amount of lights

	//Global light to generate shadows only, models are not affected by it
	//!IMPORTANT: We need to set #DEFINE in the shader to the correct amount of light
	Light* lightPoint1 = new LightPoint(vec3(5.0f, 25.0f, -9.0f), vec3(1.0f));

	Light* spotLight1 = new LightSpot(vec3(25.0f, 5.0f, 25.0f), vec3(1.0f, 0.0f, 1.0f), vec3(-0.5f, -1.0f, -0.5f), 0.1, 0.1);
	Light* spotLight2 = new LightSpot(vec3(-25.0f, 5.0f, 25.0f), vec3(0.0f, 1.0f, 1.0f), vec3(0.5f, -1.0f, -0.5f), 0.1, 0.1);
	Light* spotLight3 = new LightSpot(vec3(0.0f, 5.0f, -25.0f), vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, -1.0f, 0.5f), 0.1, 0.1);
	Light* spotLight4 = new LightSpot(vec3(0.0f, 5.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), 0.1, 0.1);

	models["ground"] = ground;
}

void Scene::update(float tick) {
	//models["bc1"]->SetRotation(vec3(0.0f, 1.0f, 0.0f), 180);
	//Update movement
	if (!IO::stopSimulation) {
		movement.updateMovements();
		//models["bc1"]->SetRotation(vec3(0.0f, 1.0f, 0.0f), models["bc1"]->GetRotationAngle() + tick * 40);
	}

	Light::updateLights();
}

void Scene::generateCars(int num) {
	for (int i = 0; i < num; i++) {
		string id = "bc" + to_string(i);
		ModelBumperCar* car = new ModelBumperCar();
		models[id] = car;
		movement.addObject(car);
		car->SetScaling(vec3(5.0f));
		car->SetPosition(vec3(rand() % 20, 0, rand() % 20));
		car->SetRotation(vec3(0.0f, 1.0f, 0.0f), rand() % 360);
	}
}

void Scene::draw(float tick) {

	update(tick);

	for (auto const& model : models) {
		model.second->Draw();
	}

	Emitter::draw();
}
