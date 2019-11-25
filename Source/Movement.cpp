#include "Movement.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;
using namespace glm;

int Movement::count = 0;

Movement* Movement::instance = 0;
Collision& Movement::collision = Collision::getInstance();

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
	movingObjects[model][6] = generateRandomFloat() / 20 + 0.1; //Car Speed, min speed is 0.1

	collision.addObject(model);
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
		
		//Is it within boundary?
		isInRange ? *objCurState = 0.0 : *objCurState = 1.0;

		//Collision detection. Returns a vector indicating which way the car is being pushed towards
		vec2 displace = collision.collisionCheck(model);

		
		vec3 newDisplacedPosition = model->GetPosition() + vec3(displace.x, 0, displace.y);

		//Forces the push to stay in range
		if (newDisplacedPosition.x >= 21) newDisplacedPosition.x = 20.9;
		if (newDisplacedPosition.x <= -21) newDisplacedPosition.x = -20.9;
		if (newDisplacedPosition.z >= 21) newDisplacedPosition.z = 20.9;
		if (newDisplacedPosition.z <= -21) newDisplacedPosition.z = -20.9;

		if (displace != vec2(0, 0)) {
			model->SetPosition(newDisplacedPosition);
			//int rotate = generateRandomFloat() > 0.8 ? 1 : 0;
			float rotationDir = *objRandNum > 0.5 ? -1 : 1;
			if (*objCurRotSteps < *objMaxRotStep) {
				model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + rotationDir * 2);
				*objCurRotSteps++;
			}
			continue;
		}

		// Obj is not stuck
		if (*objCurState == 0.0) {
			//Foward steps met?
			if (*objCurFowSteps <= *objMaxFowStep) {
				model->SetPosition(nextPosition);
				*objCurFowSteps += 1.0;
			} else { //Moved enough forward, rotate now
				if (*objCurRotSteps == 0.0) {
					*objRandNum = generateRandomFloat(); //Assign a behaviour
				}
				int rotateDir = *objRandNum >= 0.5 ? 1.0 : -1.0; //Set rotation direction
				float rotationAmount = easyEase(*objCurRotSteps / *objMaxRotStep);
				model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + rotationAmount * rotateDir);
				model->SetPosition(nextPosition); //Still make it move forward so it is smooth
				*objCurRotSteps += 1.0;
				if (*objCurRotSteps > *objMaxRotStep) { //Rotated enough, reset step counts
					*objCurRotSteps = 0.0;
					*objCurFowSteps = 0.0;
					*objRandNum = 0.0; //Resets behaviour
				}
			}
		} else { //Obj is out of bounds
			if (*objRandNum == 0.0) *objRandNum = generateRandomFloat();
			int stuckRotateDir = *objRandNum >= 0.5 ? 1 : -1;

			model->SetRotation(model->GetRotationAxis(), model->GetRotationAngle() + 2.0f * stuckRotateDir);
			//Reset setps
			*objCurRotSteps = 0.0;
			*objCurFowSteps = 0.0;
		}
	}
}

float Movement::easyEase(float t) {
	if(t <= 0.5f) return 2.0f * sqrt(t);
	t -= 0.5f;
	return 2.0f * t * (1.0f - t) + 0.5;
}