#include "Emitter.h"

using namespace std;
using namespace glm;

const vec3 Emitter::EMITTER_OFFSET = vec3(1.3f, 1.1f, 3.5f);
const int Emitter::RATE = 4;
const int Emitter::MAX_EMITTER_PARTICLES = 50;

Emitter::Emitter(ModelBumperCar* model) {
	MAX_LIFE = 120 + (int) generateRandomFloat() * 100;
	parent = model;
	particleArray = new ModelSmoke[Emitter::MAX_EMITTER_PARTICLES];
	particleMatrices = new mat4[Emitter::MAX_EMITTER_PARTICLES];
	setupInstancedArray();
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
	//kill dead particles
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		ModelSmoke* smoke = &particleArray[i];
		if (smoke->life > MAX_LIFE) {
			smoke->alive = false;
			smoke->life = 0;
		}
	}
	
	if (count % RATE == 0) {
		int i = findDeadParticle();
		ModelSmoke* smoke = &particleArray[i];
		smoke->alive = true;
		smoke->SetPosition(position);
		smoke->SetScaling(vec3(generateRandomFloat()));
		
		count = 0;
	}

	simulate();
	updateParticleMatrices();
	draw();
	count++;
}

Emitter::~Emitter() {
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		delete &particleArray[i];
	}
	delete particleArray;
	delete particleMatrices;
}

float Emitter::generateRandomFloat() {
	return rand() / (float)RAND_MAX;
}

void Emitter::simulate() {
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		ModelSmoke* smoke = &particleArray[i];
		if (smoke->alive) {
			vec3 upDir = vec3(generateRandomFloat() / 5,
				generateRandomFloat() / 15,
				generateRandomFloat() / 5);
			vec3 sizeInc = vec3(generateRandomFloat() / 3);
			//vec3 sizeExtra = generateRandomFloat() > 0.5 ? vec3(generateRandomFloat()/2, 0.0f, 0.0f) : vec3(0.0f, 0.0f, generateRandomFloat()/2);
			smoke->SetPosition(smoke->GetPosition() + upDir);
			smoke->SetScaling(smoke->GetScaling() + sizeInc);
			smoke->SetRotation(vec3(1.0f, 0.0f, 1.0f), smoke->GetRotationAngle() + generateRandomFloat() * 10);
			smoke->life++;
		}
	}
}

void Emitter::draw() {
	/*
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		ModelSmoke* smoke = &particleArray[i];
		if (smoke->alive) {
			smoke->Draw();
		}
	}
	*/
	updateInstancedArray();
	ModelSmoke::InstanceDraw();
}

int Emitter::findDeadParticle() {
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		ModelSmoke* smoke = &particleArray[i];
		if (!smoke->alive) {
			pointer = i;
			return i;
		}
	}
	
	for (int i = 0; i < pointer; i++) {
		ModelSmoke* smoke = &particleArray[i];
		if (!smoke->alive) {
			pointer = i;
			return i;
		}
	}
	
	return 0;
}

void Emitter::updateParticleMatrices() {
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		particleMatrices[i] = particleArray[i].GetWorldMatrix();
	}
}

void Emitter::setupInstancedArray() {
	//Init instanced array
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, Emitter::MAX_EMITTER_PARTICLES * sizeof(glm::mat4), 0, GL_STATIC_DRAW);
}

void Emitter::updateInstancedArray() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, Emitter::MAX_EMITTER_PARTICLES * sizeof(glm::mat4), &particleMatrices[0]);

	VAO = ModelSmoke::mVAO;

	glBindVertexArray(VAO);
	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}