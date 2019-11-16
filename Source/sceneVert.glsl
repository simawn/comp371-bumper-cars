#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aUV;
layout (location = 3) in mat4 aInstanceMatrix;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);  // default value for view matrix (identity)
uniform mat4 projectionMatrix = mat4(1.0);
uniform vec3 lightPoint;
uniform mat4 lightSpaceMatrix;

out vec3 vertexColor;
out vec2 vertexUV;
out vec3 positionWorld;
out vec3 eyeDirectionCam;
out vec3 normCam;
out vec3 lightDirectionCam;
out vec4 FragPosLightSpace;
out vec3 FragPos;

//Switch for instanced rendering (smoke)
uniform int instanced = 0;

void main(){
	
	//Instanced rendering setup

	mat4 aWorldMatrix = worldMatrix;

	if(instanced == 1) {
		aWorldMatrix = aInstanceMatrix;
	}


	mat4 modelViewProjection = projectionMatrix * viewMatrix * aWorldMatrix;
	gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	
	//
	//Lighting
	//

	positionWorld = (aWorldMatrix * vec4(aPos, 1)).xyz;
	vec3 positionCamera = (viewMatrix * aWorldMatrix * vec4(aPos, 1)).xyz;
	eyeDirectionCam = vec3(0.0f, 0.0f, 0.0f)  - positionCamera;
	vec3 lightPosCam = (viewMatrix * vec4(lightPoint, 1)).xyz;
	lightDirectionCam = lightPosCam + eyeDirectionCam;
	normCam = (viewMatrix * aWorldMatrix * vec4(aNorm, 0)).xyz;

	//
	//UV
	//

	vertexUV = vec2(aUV.x, aUV.y);

	//
	//Shadows
	//
	FragPos = vec3(aWorldMatrix * vec4(aPos, 1.0));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
};