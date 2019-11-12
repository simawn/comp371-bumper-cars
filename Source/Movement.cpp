#include "Movement.h"

using namespace std;
using namespace glm;

Movement* Movement::instance = 0;

Movement& Movement::getInstance() {
	if (instance == 0) instance = new Movement();
	return *instance;
}

Movement::Movement() {}

void Movement::addObject(Model * model) {
	movingObjects.push_back(model);
}

void Movement::updateMovements() {
	for (Model* model : movingObjects) {
		model->SetPosition(model->GetPosition() + vec3(0.01, 0, 0.01));
	}
}
