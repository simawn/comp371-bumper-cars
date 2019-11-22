#include "ModelBumperCar.h"
#include "Renderer.h"

using namespace std;
vector<objl::Mesh> ModelBumperCar::obj = {};

ModelBumperCar::ModelBumperCar() {
	//Loads the model once
	if(obj.empty()) obj = loadObj("../Models/bumperCar_3.obj");

	/*
	int clampCol = 1.6;
	diffuseColor = vec3(rand() / (float)RAND_MAX / clampCol, 
						rand() / (float)RAND_MAX / clampCol, 
						rand() / (float)RAND_MAX / clampCol);
	*/

	//Limit to shades of cmy
	float rng = rand() / (float)RAND_MAX;
	if (rng < 0.3) rng += 0.3;
	vec3 colors[] = { vec3(0, rng, rng), vec3(rng, 0, rng), vec3(rng, rng, 0) };

	diffuseColor = colors[(int) (rng * 1000) % 3];

	for (objl::Mesh mesh : obj) {
		meshes.push_back(make_tuple(mesh, setupMeshEBO(mesh), mesh.Vertices.size()));
	}

	emitter = new Emitter(this);

	//Backlight
	float cutOff = 1;
	float outerCutOff = 0.9;

	//Back right
	lightPosOffsets[0] = vec3(0.85f, 2.2f, 3.3f);
	lightDirOffsets[0] = vec3(0.0f, -0.5f, 1.0f);
	lightColors[0] = vec3(1.0f, 0.0f, 0.0f);
	lights[0] = new LightSpot(lightPosOffsets[0], lightColors[0], lightDirOffsets[0], cutOff, outerCutOff);
	//Back left
	lightPosOffsets[1] = vec3(-0.85f, 2.2f, 3.3f);
	lightDirOffsets[1] = vec3(0.0f, -0.5f, 1.0f);
	lightColors[1] = vec3(1.0f, 0.0f, 0.0f);
	lights[1] = new LightSpot(lightPosOffsets[1], lightColors[1], lightDirOffsets[1], cutOff, outerCutOff);
	//Front left
	lightPosOffsets[2] = vec3(-1.05f, 1.15f, -3.3f);
	lightDirOffsets[2] = vec3(0.0f, -0.5f, -1.0f);
	lightColors[2] = vec3(1.0f, 1.0f, 1.0f);
	lights[2] = new LightSpot(lightPosOffsets[2], lightColors[2], lightDirOffsets[2], cutOff, outerCutOff);
	//Front right
	lightPosOffsets[3] = vec3(1.05f, 1.15f, -3.3f);
	lightDirOffsets[3] = vec3(0.0f, -0.5f, -1.0f);
	lightColors[3] = vec3(1.0f, 1.0f, 1.0f);
	lights[3] = new LightSpot(lightPosOffsets[3], lightColors[3], lightDirOffsets[3], cutOff, outerCutOff);
}

ModelBumperCar::~ModelBumperCar() {
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
	delete emitter;
}

void ModelBumperCar::Update(float dt) {
	for (int i = 0; i < 4; i++) {
		Light* light = lights[i];

		vec3 curLightPos = light->getPosition();
		vec3 curDirection = light->getDirection();

		light->setPosition(this->GetPosition() + rotate(lightPosOffsets[i], radians(this->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f)));
		light->setDirection(rotate(lightDirOffsets[i], radians(this->GetRotationAngle() + 180), vec3(0.0f, 1.0f, 0.0f)));
	
		if (!IO::stopLights) {
			lightColors[i] = i <= 1 ? vec3(1.0f, 0.0f, 0.0f) : vec3(1.0f);
		}
		else {
			lightColors[i] = vec3(0.0f);
		}

		light->setColor(lightColors[i]);
	}
}

void ModelBumperCar::Draw() {
	this->Update(0);

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
