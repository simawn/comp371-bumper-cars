#include "ModelBumperCar.h"
//#include "OBJloaderV2.h"
#include "Renderer.h"

ModelBumperCar::ModelBumperCar() {
	vector<objl::Mesh> obj = loadObj("../Models/bumperCar_2.obj");
	for (objl::Mesh mesh : obj) {
		meshes[setupMeshEBO(mesh)] = mesh.Vertices.size();
	}
}

ModelBumperCar::~ModelBumperCar() {
}

void ModelBumperCar::Update(float dt) {
}

void ModelBumperCar::Draw() {
	for (auto const& mesh : meshes) {
		glBindVertexArray(mesh.first);
		Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
		glDrawElements(GL_TRIANGLES, mesh.second, GL_UNSIGNED_INT, 0);
	}
}
