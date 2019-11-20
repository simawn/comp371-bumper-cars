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

//Properties from obj
uniform vec3 specColor = vec3(0.3, 0.3, 0.3);
uniform int specExp = 255;
uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0);

out vec4 FragColor;

//All the light calculations from: https://learnopengl.com/Lighting/Multiple-lights
//Point Light

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos);  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

	vec3 N = normalize(normCam);
	vec3 L = normalize(lightDirectionCam);
	vec3 E = normalize(eyeDirectionCam);
	vec3 R = reflect(-L, N);

    float spec = pow(max(dot(E, R), 0.0), specExp);
    // attenuation
    float distance    = length(light.position - positionWorld);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * diffuseColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * diffuseColor;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

//Directional Light

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcDirLight(DirLight light, vec3 normal);

vec3 CalcDirLight(DirLight light, vec3 normal) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading

	vec3 N = normalize(normCam);
	vec3 L = normalize(lightDirectionCam);
	vec3 E = normalize(eyeDirectionCam);
	vec3 R = reflect(-L, N);

    float spec = pow(max(dot(E, R), 0.0), specExp);

    // combine results
	vec3 ambient  = light.ambient  * diffuseColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * diffuseColor;
    return (ambient + diffuse + specular);
} 

//Light Uniforms
#define NR_POINT_LIGHTS 4
#define NR_DIR_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLights[NR_DIR_LIGHTS];

//Shadows

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
	//Shadows
	//
	float shadow = shadowCalc(dot(lightDirectionCam, normCam));

	//
	//Lights
	//
	vec3 result;

	//Point Lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], normCam, FragPos); 
	}

	//Dir Lights
	for(int i = 0; i < NR_DIR_LIGHTS; i++) {
        result += CalcDirLight(dirLights[i], normCam);
	}

	//
	//Overall ambient
	//
	vec3 ambientIntensity = vec3(0.6f);
	vec3 ambient = ambientColor * diffuseColor.rgb * ambientIntensity;

	//
	//Output
	//
	FragColor = vec4(ambient + (1.0f - shadow) * result, 1.0f);
}