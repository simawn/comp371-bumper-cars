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
	movingObjects[model][0] = 0.0; //Random float for behaviour
	movingObjects[model][1] = generateRandomFloat() * 20 + 60; //Max foward Step
	movingObjects[model][2] = 0.0; //Current foward step
	movingObjects[model][3] = generateRandomFloat() * 20 + 60; //Max rotate step
	movingObjects[model][4] = 0.0; //Current rotate step
	movingObjects[model][5] = 0.0; //state: stuck or unstuck
	movingObjects[model][6] = generateRandomFloat() / 3 + 0.1; //Car Speed
}

void Movement::updateMovements() {
	for (auto& object : movingObjects) {
		Model* model = object.first;
		float* objRandNum = &object.second[0];
		float* objMaxFowStep = &object.second[1];
		float* objCurFowSteps = &object.second[2];
		float* objMaxRotStep = &object.second[3];
		float* objCurRotSteps = &object.second[4];
		float* objCurState = &object.second[5];
		float* objCarSpeed = &object.second[6];

		float r = *objCarSpeed;
		
		vec3 carPosition = model ->GetPosition();
		//Move forward only if in range
		vec3 nextPosition = carPosition + vec3(r * cos(radians(model->GetRotationAngle() - 90)),
												0,
												r * sin(radians(model->GetRotationAngle() + 90))
												);
		bool isInRange = nextPosition.x >= -21 && nextPosition.x <= 21 && nextPosition.z >= -21 && nextPosition.z <= 21;
		
		isInRange ? *objCurState = 0.0 : *objCurState = 1.0;

		// Obj is not stuck
		if (*objCurState == 0.0) {
			*objRandNum = 0.0; //Resets behaviour
			//Foward steps met?
			if (*objCurFowSteps <= *objMaxFowStep) {
				model->SetPosition(nextPosition);
				*objCurFowSteps += 1.0;
			} else { //Moved enough forward, rotate now
				if (*objCurRotSteps == 0.0) {
					*objRandNum = generateRandomFloat(); //Assign a behaviour
				}
				int rotateDir = *objRandNum >= 0.5 ? 1.0 : -1.0;
				model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + generateRandomFloat() * 3.0 * rotateDir);
				model->SetPosition(nextPosition); //Still make it move forward so it is smooth
				*objCurRotSteps += 1.0;
				if (*objCurRotSteps > *objMaxRotStep) { //Rotated enough, reset step counts
					*objCurRotSteps = 0.0;
					*objCurFowSteps = 0.0;
				}
			}
		} else { //Obj is stuck, force turn it
			if (*objRandNum == 0.0) *objRandNum = generateRandomFloat();
			int stuckRotateDir = *objRandNum >= 0.5 ? 1 : -1;
			model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + 3 * stuckRotateDir);
			//Reset setps
			*objCurRotSteps = 0.0;
			*objCurFowSteps = 0.0;
		}
	}
}
