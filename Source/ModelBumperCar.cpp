#include "ModelBumperCar.h"
#include "OBJloaderV2.h"
#include "Renderer.h"

ModelBumperCar::ModelBumperCar() {
	bumperCarVAO = setupModelEBO("../Models/bumperCar_2.obj", bumperCarVertices);
}

ModelBumperCar::~ModelBumperCar() {
}

void ModelBumperCar::Update(float dt) {
}

void ModelBumperCar::Draw() {
	glBindVertexArray(bumperCarVAO);
	Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
	glDrawElements(GL_TRIANGLES, bumperCarVertices, GL_UNSIGNED_INT, 0);
}
