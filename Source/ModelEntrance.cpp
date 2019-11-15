#include "ModelEntrance.h"

vector<objl::Mesh> ModelEntrance::obj = {};

ModelEntrance::ModelEntrance() {
	if(obj.empty()) obj = loadObj("../Models/entrance.obj");

	for (objl::Mesh mesh : obj) {
		meshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
	}
}

ModelEntrance::~ModelEntrance() {
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void ModelEntrance::Update(float dt) {
}

void ModelEntrance::Draw() {
	for (auto const& mesh : meshes) {
		glBindVertexArray(get<1>(mesh));
		Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
		objl::Material meshMat = get<0>(mesh).MeshMaterial;

		Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));

		//Other properties
		Renderer::setSpecColor(vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z));
		Renderer::setSpecExp(meshMat.Ns);
		Renderer::setAmbientColor(vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z));

		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);
	}
}
