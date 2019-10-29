//Modified code from https://www.opengl-tutorial.org/

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aUV;
layout (location = 3) in vec3 aNorm;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;  // default value for view matrix (identity)
uniform mat4 projectionMatrix;
uniform vec3 lightPosWorld;
uniform mat4 lightSpaceMatrix;

out vec3 vertexColor;
out vec2 vertexUV;
out vec3 positionWorld;
out vec3 eyeDirectionCam;
out vec3 normCam;
out vec3 lightDirectionCam;
out vec4 FragPosLightSpace;
out vec3 FragPos;

void main()
{
   //vertexColor = aColor;
   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;
   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);

   //Position of vertex 
   positionWorld = (worldMatrix * vec4(aPos, 1)).xyz;

   //Vector pointing the camera, camera space
   vec3 positionCamera = (viewMatrix * worldMatrix * vec4(aPos, 1)).xyz;
   eyeDirectionCam = vec3(0.0f, 0.0f, 0.0f) - positionCamera;

   //Light 
   vec3 lightPosCam = (viewMatrix * vec4(lightPosWorld, 1)).xyz;
   lightDirectionCam = lightPosCam + eyeDirectionCam;

   //Normal camera space
   normCam = (viewMatrix * worldMatrix * vec4(aNorm, 0)).xyz;

   //Shadows
   //FragPos = vec3(worldMatrix * vec4(aPos, 1.0));
   FragPos = vec3(worldMatrix * vec4(aPos, 1.0));
   FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

   vertexUV = vec2(aUV.x, aUV.y);
}
