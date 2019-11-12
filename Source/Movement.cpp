#include "Movement.h"
#include <glm/gtx/string_cast.hpp>

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
	movingObjects[model] = 0.0;
}

void Movement::updateMovements() {
	for (auto const& object : movingObjects) {
		Model* model = object.first;

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
		float r = 0.15; // Car speed
		
		vec3 carPosition = model ->GetPosition();
		//Move forward only if in range
		vec3 nextPosition = carPosition + vec3(r * cos(radians(model->GetRotationAngle() - 90)),
												0,
												r * sin(radians(model->GetRotationAngle() + 90))
												);
		bool isInRange = nextPosition.x >= -21 && nextPosition.x <= 21 && nextPosition.z >= -21 && nextPosition.z <= 21;
		
		if (isInRange) {
			movingObjects[model] = 0.0;
			model->SetPosition(nextPosition);
		}

		if (!isInRange) {
			if (object.second == 0.0) movingObjects[model] = generateRandomFloat();
			int stuckRotateDir = object.second >= 0.5 ? 1 : -1;
			model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + 3 * stuckRotateDir);
		} else {
			if (generateRandomFloat() < 0.3) {
				model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + generateRandomFloat() * 10 * rotate * rotateDir);
			}
		}
	}
}
