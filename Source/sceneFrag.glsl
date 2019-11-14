#version 330 core
uniform vec3 diffuseColor; //overwrites other colors
uniform vec3 lightPoint;

in vec2 vertexUV;
in vec3 normCam;
in vec3 eyeDirectionCam;
in vec3 lightDirectionCam;
in vec3 positionWorld;

in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D textureSampler;

uniform sampler2D shadowMap;

out vec4 FragColor;

float shadowCalc(float dotLightNormal){
    vec3 projCoords = (FragPosLightSpace.xyz / FragPosLightSpace.w) * 0.5 + 0.5;

	//In case values are greater than 1
	if(projCoords.z > 1.0) {
		projCoords.z = 1.0;
	}
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	//bias to eliminate moire pattern
	//Removed bias for point light
	//float bias = max(0.005 * (1.0 - dotLightNormal), 0.0005);
	float bias = 0.0005;
    // check whether current frag pos is in shadow
    float shadow = 0.0;
	//Smoother shadows
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
			//shadow += currentDepth > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 12.0;

    return shadow;
}

void main() {
	//
	// Material
	//
	//vec3 matDiffuseColor = texture(textureSampler, vertexUV).rgb;
	vec3 matDiffuseColor = diffuseColor.rgb;
	vec3 matAmbientColor = vec3(0.5f, 0.5f, 0.5f) * matDiffuseColor;
	vec3 matSpecColor = vec3(0.3, 0.3, 0.3);

	//
	// Lighting
	//
	//Light params
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float lightPower = 250.0f;
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

	//
	//Shadows
	//
	float shadow = shadowCalc(dot(lightDirectionCam, normCam));

	//output
	FragColor = vec4(matAmbientColor + (1.0f - shadow) * (matDiffuse + matSpecColor), 1.0f);
}