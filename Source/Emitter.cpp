#include "Emitter.h"

using namespace std;
using namespace glm;

const vec3 Emitter::EMITTER_OFFSET = vec3(1.3f, 1.1f, 3.5f);

Emitter::Emitter(ModelBumperCar* model) {
	MAX_LIFE = 120 + (int) generateRandomFloat() * 100;
	parent = model;
}

void Emitter::setPosition(vec3 newPosition) {
	
	position = newPosition + rotate(EMITTER_OFFSET, radians(parent->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f));
	
	/*
	ModelSmoke indicator = ModelSmoke();
	indicator.SetScaling(vec3(4.0f));
	indicator.SetPosition(position);
	indicator.Draw();
	*/
}

void Emitter::generateParticles() {
	//Kill old particles
	//Use array instead?
	for (auto it = particleArray.begin(); it != particleArray.end();) {
		if ((*it)->life > MAX_LIFE) {
			delete (*it);
			it = particleArray.erase(it);
		} else {
			++it;
		}
	}
	
	if (count % RATE == 0) {
		ModelSmoke* smokePart = new ModelSmoke();
		smokePart->SetPosition(position);
		particleArray.push_back(smokePart);
		count = 0;
	}

	simulate();
	draw();
	count++;
}

float Emitter::generateRandomFloat() {
	return rand() / (float)RAND_MAX;
}

void Emitter::simulate() {
	
	for (auto &particle : particleArray) {
		vec3 upDir = vec3(generateRandomFloat() / 5, 0.07f, generateRandomFloat() / 5);
		vec3 sizeInc = vec3(0.1f);
		particle->SetPosition(particle->GetPosition() + upDir);
		particle->SetScaling(particle->GetScaling() + sizeInc);
		particle->SetRotation(vec3(1.0f, 0.0f, 1.0f), generateRandomFloat() * 100);
		particle->life++;
	}
}

void Emitter::draw() {
	for (auto const &particle : particleArray) {
		particle->Draw();
	}
}
