#include "Emitter.h"

using namespace std;
using namespace glm;

const vec3 Emitter::EMITTER_OFFSET = vec3(1.3f, 1.1f, 3.5f);
const int Emitter::RATE = 1;
const int Emitter::MAX_EMITTER_PARTICLES = 1000;
mat4* Emitter::particleMatrices = new mat4[Emitter::MAX_EMITTER_PARTICLES];
unsigned int Emitter::buffer;
unsigned int Emitter::VAO;
vector<ModelSmoke*> Emitter::particleArray = {};

Emitter::Emitter(ModelBumperCar* model) {
	MAX_LIFE = 75 + (int) generateRandomFloat() * 100;
	parent = model;
	
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
	
	for (auto it = particleArray.begin(); it != particleArray.end();) {
		if ((*it)->life > MAX_LIFE) {
			delete *it;
			it = particleArray.erase(it);
		} else {
			++it;
		}
	}
	
	if (count % RATE == 0) {
		ModelSmoke* smokePart = new ModelSmoke();
		smokePart->SetPosition(position);
		smokePart->SetScaling(vec3(generateRandomFloat() * 7));
		if (particleArray.size() < Emitter::MAX_EMITTER_PARTICLES) {
			particleArray.push_back(smokePart);
		}
		count = 0;
	}

	
	
	//draw();
	count++;
}

Emitter::~Emitter() {
	for (auto it = particleArray.begin(); it != particleArray.end();) {
		delete (*it);
	}
	delete particleMatrices;
	glDeleteBuffers(1, &buffer);
}

float Emitter::generateRandomFloat() {
	return rand() / (float)RAND_MAX;
}

void Emitter::simulate() {
	for (auto &particle : particleArray) {
		vec3 upDir = vec3(generateRandomFloat() / 5,
						  generateRandomFloat() / 10,
						  generateRandomFloat() / 5);
		vec3 sizeInc = vec3(generateRandomFloat() / 3);
		//vec3 sizeExtra = generateRandomFloat() > 0.5 ? vec3(generateRandomFloat()/2, 0.0f, 0.0f) : vec3(0.0f, 0.0f, generateRandomFloat()/2);
		particle->SetPosition(particle->GetPosition() + upDir);
		particle->SetScaling(particle->GetScaling() + sizeInc);
		particle->SetRotation(vec3(1.0f, 0.0f, 1.0f), particle->GetRotationAngle() + generateRandomFloat() * 10);
		particle->life++;
	}
}

void Emitter::draw() {
	simulate();
	updateParticleMatrices();
	updateInstancedArray();
	ModelSmoke::InstanceDraw();
}

void Emitter::updateParticleMatrices() {
	//Clear matrix
	for (int i = 0; i < Emitter::MAX_EMITTER_PARTICLES; i++) {
		particleMatrices[i] = mat4();
	}
	//Add content
	int counter = 0;
	for (auto &particle : particleArray) {
		particleMatrices[counter] = particle->GetWorldMatrix();
		counter++;
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