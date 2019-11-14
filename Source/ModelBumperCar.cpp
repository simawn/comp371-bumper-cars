#include "ModelBumperCar.h"
#include "Renderer.h"

using namespace std;
vector<objl::Mesh> ModelBumperCar::obj = {};

ModelBumperCar::ModelBumperCar() {
	//Loads the model once
	if(obj.empty()) obj = loadObj("../Models/bumperCar_3.obj");
	
	diffuseColor = vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);

	for (objl::Mesh mesh : obj) {
		meshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
	}

	emitter = new Emitter();
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

		//Randomizes body color
		if (get<0>(mesh).MeshName == "body_Cube.005") { 
			Renderer::setDiffuseColor(diffuseColor);
		} else {
			Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));
		}

		//Other properties
		Renderer::setSpecColor(vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z));
		Renderer::setSpecExp(meshMat.Ns);
		Renderer::setAmbientColor(vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z));

		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);
	}

	//Update emitter and draw particles
	emitter->setPosition(this->GetPosition());
	emitter->generateParticles();
}
