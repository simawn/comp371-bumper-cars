#include "ModelField.h"

vector<objl::Mesh> ModelField::obj = {};

using namespace std;
using namespace glm;

ModelField::ModelField() {
	if(obj.empty()) obj = loadObj("../Models/groundTile.obj");

	for (objl::Mesh mesh : obj) {
		meshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
	}

	// TODO: Load textures from .mtl file
	// Note: Texture scaling was modified directly in .obj file (vt)
#if defined(PLATFORM_OSX)
	textureID = Renderer::loadTexture("../Assets/Textures/tile.jpg");
#else
	textureID = Renderer::loadTexture("../Assets/Textures/tile.jpg");
#endif
	
}

ModelField::~ModelField() {
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void ModelField::Update(float dt) {
}

void ModelField::Draw() {
	for (auto const& mesh : meshes) {
		glBindVertexArray(get<1>(mesh));
		Renderer::setWorldMatrix(Shaders::currentShaderProgram, GetWorldMatrix());
		objl::Material meshMat = get<0>(mesh).MeshMaterial;

		Renderer::setDiffuseColor(vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z));


		//Other properties
		Renderer::setSpecColor(vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z));
		Renderer::setSpecExp(meshMat.Ns);
		Renderer::setAmbientColor(vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z));

		//Texture
		//Set flag to use texture
		GLuint textureFlag = glGetUniformLocation(Shaders::currentShaderProgram, "useTexture");
		glUniform1i(textureFlag, 1);

		Renderer::useTexture(textureID);

		glDrawElements(GL_TRIANGLES, get<2>(mesh), GL_UNSIGNED_INT, 0);

		glUniform1i(textureFlag, 0);
	}
}
