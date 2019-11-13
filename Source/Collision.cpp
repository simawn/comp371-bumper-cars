#include "Collision.h"

using namespace std;
using namespace glm;

Collision* Collision::instance = 0;

Collision& Collision::getInstance() {
	if (instance == 0) instance = new Collision();
	return *instance;
}

void Collision::addObject(Model* model) {
	collisionObjects.push_back(model);
}

bool Collision::IsColliding(Model * model) {

	return false;
}

Collision::Collision() {}

