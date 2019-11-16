#include "ModelSmoke.h"

vector<objl::Mesh> ModelSmoke::obj = {};
vector<tuple<objl::Mesh, GLuint, int>> ModelSmoke::smokeMeshes = {};
unsigned int ModelSmoke::mVAO = 0;

ModelSmoke::ModelSmoke() {
	//Loads the model once
	if (obj.empty()) {
		obj = loadObj("../Models/smoke.obj");
		for (objl::Mesh mesh : obj) {
			smokeMeshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
		}
		ModelSmoke::mVAO = get<1>(smokeMeshes.front());
	}
	
	float b = 0.4 + ((float) rand() / RAND_MAX) / 3;

	color = vec3(b, b, b);
}

ModelSmoke::~ModelSmoke() {
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void ModelSmoke::Update(float dt) {
}

void ModelSmoke::Draw() {
	/*
	for (auto const& mesh : meshes) { //smokeMeshes
		glBindVertexArray(get<1>(mesh));
		Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
		objl::Material meshMat = get<0>(mesh).MeshMaterial;
		
		//Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));
		Renderer::setDiffuseColor(color);

		//Other properties
		Renderer::setSpecColor(vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z));
		Renderer::setSpecExp(meshMat.Ns);
		Renderer::setAmbientColor(vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z));

		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);
	}
	*/
	
}

void ModelSmoke::InstanceDraw() {
	glUseProgram(Shaders::currentShaderProgram);

	//Renderer::setDiffuseColor(color); //Need another way to load colors

	//Other properties
	objl::Material meshMat = get<0>(smokeMeshes.front()).MeshMaterial;

	Renderer::setSpecColor(vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z));
	Renderer::setSpecExp(meshMat.Ns);
	Renderer::setAmbientColor(vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z));


	//enable instancing
	glUniform1i(glGetUniformLocation(Shaders::currentShaderProgram, "instanced"), 1);
	glBindVertexArray(ModelSmoke::mVAO);
	glDrawElementsInstanced(GL_TRIANGLES, get<2>(smokeMeshes.front()), GL_UNSIGNED_INT, 0, Emitter::MAX_EMITTER_PARTICLES);
	glBindVertexArray(0);
	//disable instancing
	glUniform1i(glGetUniformLocation(Shaders::currentShaderProgram, "instanced"), 0);
}

