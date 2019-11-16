//Modified code from https://www.opengl-tutorial.org/

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 aInstanceMatrix;

uniform mat4 lightSpaceMatrix;
uniform mat4 worldMatrix;

//Switch for instanced rendering (smoke)
uniform int instanced = 0;

void main() {
	//Instanced rendering setup

	mat4 aWorldMatrix = worldMatrix;

	if(instanced == 1) {
		aWorldMatrix = aInstanceMatrix;
	}

    gl_Position = lightSpaceMatrix * aWorldMatrix * vec4(aPos, 1.0);
}  