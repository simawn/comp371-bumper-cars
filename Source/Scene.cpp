#include "Scene.h"

Scene* Scene::instance = 0;

Scene& Scene::getInstance() {
	if(instance == 0) instance = new Scene();
	return *instance;
}

Scene::Scene() {

}

void Scene::draw() {
	for (Model model : models) {
		model.draw();
	}
}
