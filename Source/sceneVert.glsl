#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aUV;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);  // default value for view matrix (identity)
uniform mat4 projectionMatrix = mat4(1.0);
uniform vec3 lightPoint;

out vec3 vertexColor;
out vec2 vertexUV;
out vec3 positionWorld;
out vec3 eyeDirectionCam;
out vec3 normCam;
out vec3 lightDirectionCam;

void main(){
	mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
	gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	
	//
	//Lighting
	//

	positionWorld = (worldMatrix * vec4(aPos, 1)).xyz;
	vec3 positionCamera = (viewMatrix * worldMatrix * vec4(aPos, 1)).xyz;
	eyeDirectionCam = vec3(0.0f, 0.0f, 0.0f)  - positionCamera;
	vec3 lightPosCam = (viewMatrix * vec4(lightPoint, 1)).xyz;
	lightDirectionCam = lightPosCam + eyeDirectionCam;
	normCam = (viewMatrix * worldMatrix * vec4(aNorm, 0)).xyz;

	//
	//UV
	//

	vertexUV = vec2(aUV.x, aUV.y);
};