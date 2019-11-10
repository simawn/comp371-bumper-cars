#version 330 core
uniform vec3 diffuseColor; //overwrites other colors
uniform vec3 lightPoint;

in vec2 vertexUV;
in vec3 normCam;
in vec3 eyeDirectionCam;
in vec3 lightDirectionCam;
in vec3 positionWorld;

uniform sampler2D textureSampler;

out vec4 FragColor;

void main() {
	//
	// Material
	//
	//vec3 matDiffuseColor = texture(textureSampler, vertexUV).rgb;
	vec3 matDiffuseColor = diffuseColor.rgb;
	vec3 matAmbientColor = vec3(0.2f, 0.2f, 0.2f) * matDiffuseColor;
	vec3 matSpecColor = vec3(0.3, 0.3, 0.3);

	//
	// Lighting
	//
	//Light params
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float lightPower = 50.0f;
	//
	float distance = length(lightPoint - positionWorld);
	
	vec3 N = normalize(normCam);
	vec3 L = normalize(lightDirectionCam);
	float cosTheta = clamp(dot(N, L), 0, 1);

	vec3 E = normalize(eyeDirectionCam);
	vec3 R = reflect(-L, N);
	float cosAlpha = pow(max(dot(E, R), 0.0), 64);

	vec3 matDiffuse = matDiffuseColor * lightColor * lightPower * cosTheta / (distance * distance);
	vec3 matSpecualar = matSpecColor * lightColor * cosAlpha * 32;

	//output
	FragColor = vec4(matAmbientColor + matDiffuse + matSpecColor, 1.0f);
	//FragColor = vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0f);
}