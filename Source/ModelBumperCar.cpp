#include "ModelBumperCar.h"
//#include "OBJloaderV2.h"
#include "Renderer.h"

using namespace std;

ModelBumperCar::ModelBumperCar() {
	vector<objl::Mesh> obj = loadObj("../Models/bumperCar_2.obj");
	for (objl::Mesh mesh : obj) {
		meshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
	}
}

ModelBumperCar::~ModelBumperCar() {
}

void ModelBumperCar::Update(float dt) {
}

void ModelBumperCar::Draw() {
	for (auto const& mesh : meshes) {
		glBindVertexArray(get<1>(mesh));
		Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
		objl::Material meshMat = get<0>(mesh).MeshMaterial;
		Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));
		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);
	}
}
