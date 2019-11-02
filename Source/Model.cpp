//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Model::Model() :	mPosition(0.0f, 0.0f, 0.0f), 
					mScaling(1.0f, 1.0f, 1.0f), 
					mRotationAxis(0.0f, 1.0f, 0.0f),
					mRotationAngleInDegrees(0.0f)
{}

Model::~Model() {}

void Model::Update(float dt) {}

void Model::Draw() {}

glm::mat4 Model::GetWorldMatrix() const {
	mat4 worldMatrix(1.0f);

	mat4 t = glm::translate(mat4(1.0f), mPosition);
	mat4 r = glm::rotate(mat4(1.0f), glm::radians(mRotationAngleInDegrees), mRotationAxis);
	mat4 s = glm::scale(mat4(1.0f), mScaling);
	worldMatrix = t * r * s;

	return worldMatrix;
}

void Model::SetPosition(glm::vec3 position) {
	mPosition = position;
}

void Model::SetScaling(glm::vec3 scaling) {
	mScaling = scaling;
}

void Model::SetRotation(glm::vec3 axis, float angleDegrees) {
	mRotationAxis = axis;
	mRotationAngleInDegrees = angleDegrees;
}
