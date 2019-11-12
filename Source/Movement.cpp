#include "Movement.h"

using namespace std;
using namespace glm;

Movement* Movement::instance = 0;

Movement& Movement::getInstance() {
	if (instance == 0) instance = new Movement();
	return *instance;
}

Movement::Movement() {
	srand(time(0));
}

float Movement::generateRandomFloat() {
	return rand() / (float) RAND_MAX;
}

void Movement::addObject(Model * model) {
	movingObjects.push_back(model);
}

void Movement::updateMovements() {
	for (Model* model : movingObjects) {
		int axisX = 0; // 1 OR 0
		int axisZ = 0; // 1 OR 0
		int rotate = 0; // 1 OR 0
		int rotateDir = 1; // 1 OR -1
		int dirX = 1; // 1 OR -1
		int dirZ = 1; // 1 OR -1
		generateRandomFloat() >= 0.5 ? axisX = 1 : axisX = 0;
		generateRandomFloat() >= 0.5 ? axisZ = 1 : axisZ = 0;
		generateRandomFloat() >= 0.5 ? rotate = 1 : rotate = 0;
		generateRandomFloat() >= 0.5 ? rotateDir = -1 : rotateDir = 1;
		generateRandomFloat() >= 0.5 ? dirX = -1 : dirX = 1;
		generateRandomFloat() >= 0.5 ? dirZ = -1 : dirZ = 1;

		model->SetPosition(model->GetPosition() + vec3(generateRandomFloat() * axisX * dirX, 0, generateRandomFloat() * axisZ * dirZ));
		model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + generateRandomFloat() * 10 * rotate * rotateDir);
	}
}
