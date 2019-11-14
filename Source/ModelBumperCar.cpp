#include "ModelBumperCar.h"
//#include "OBJloaderV2.h"
#include "Renderer.h"

using namespace std;
vector<objl::Mesh> ModelBumperCar::obj = {};

ModelBumperCar::ModelBumperCar() {
	//Loads the model once
	if(obj.empty()) obj = loadObj("../Models/bumperCar_2.obj");
	
	diffuseColor = vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);

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
		if (get<0>(mesh).MeshName == "body_Cube.005") { //Randomizes body color
			Renderer::setDiffuseColor(diffuseColor);
		} else {
			Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));
		}
		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);
	}
}
