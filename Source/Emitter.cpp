#include "Emitter.h"

using namespace std;
using namespace glm;

Emitter::Emitter() {
	cout << "emiiter init" << endl;
}

void Emitter::setPosition(vec3 newPosition) {
	position = newPosition;
}

void Emitter::generateParticles() {
	//Kill old particles
	
	for (auto it = particleArray.begin(); it != particleArray.end();) {
		if ((*it)->life > MAX_LIFE) {
			delete (*it);
			it = particleArray.erase(it);
		} else {
			++it;
		}
	}
	

	if (particleArray.size() <= MAX_PARTICLES && count % RATE == 0) {
		ModelSmoke* smokePart = new ModelSmoke();
		smokePart->SetPosition(position);
		particleArray.push_back(smokePart);
		count = 0;
	}
	simulate();
	draw();
	count++;
}

void Emitter::simulate() {
	vec3 upDir = vec3(0.0f, 0.1f, 0.0f);
	vec3 sizeInc = vec3(0.1f);
	for (auto &particle : particleArray) {
		particle->SetPosition(particle->GetPosition() + upDir);
		particle->SetScaling(particle->GetScaling() + sizeInc);
		particle->life++;
	}
}

void Emitter::draw() {
	for (auto const &particle : particleArray) {
		particle->Draw();
	}
}
