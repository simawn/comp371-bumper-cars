//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#pragma once
#define GLEW_STATIC 1
//#include "OBJloaderV2.h"
#include "OBJ_Loader.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

class Model
{
public:
	Model();
	virtual ~Model();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	virtual glm::mat4 GetWorldMatrix() const;

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetRotation(glm::vec3 axis, float angleDegrees);

	glm::vec3 GetPosition() const		{ return mPosition; }
	glm::vec3 GetScaling() const		{ return mScaling; }
	glm::vec3 GetRotationAxis() const	{ return mRotationAxis; }
	float     GetRotationAngle() const	{ return mRotationAngleInDegrees; }
	GLuint setupMeshEBO(objl::Mesh);
	vector<objl::Mesh> loadObj(string path);
	map<GLuint, int> meshes;
protected:
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;
	vector<int> vertIndices;
	vector<vec3> verts;
	vector<vec2> uvs;
	vector<vec3> norms;
};
