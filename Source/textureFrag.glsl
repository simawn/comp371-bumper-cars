//Modified code from https://www.opengl-tutorial.org/

#version 330 core
in vec3 vertexColor;
in vec2 vertexUV;
in vec3 normCam;
in vec3 eyeDirectionCam;
in vec3 lightDirectionCam;
in vec3 positionWorld;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D textureSampler;
uniform sampler2D shadowMap;


uniform vec3 lightPosWorld;
uniform vec3 mainColor;
uniform int useColor;
uniform float specStrength;
uniform float specHighlight;
uniform vec3 matSpecColor;
uniform int enableShadow;

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
	//float bias = 0.005;
    // check whether current frag pos is in shadow
    float shadow = 0.0;
	//Smoother shadows
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			//shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
			shadow += currentDepth > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 12.0;

    return shadow;
}

void main()
{
	
	//Light intensity
	//TOOD: make them uniform
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float lightPower = 500.0f;

	//Material properties
	vec3 matDiffuseColor = texture(textureSampler, vertexUV).rgb;
	vec3 matAmbientColor = vec3(0.4f, 0.4f, 0.4f) * matDiffuseColor;

	//Distance to the light
	float distance = length(lightPosWorld - positionWorld);

	//Normals 
	vec3 n = normalize(normCam);
	vec3 l = normalize(lightDirectionCam);

	//Angle
	float cosTheta = clamp(dot(n, l), 0, 1);

	//Eye vector
	vec3 E = normalize(eyeDirectionCam);
	vec3 R = reflect(-l, n); //letter L
	float cosAlpha = pow(max(dot(E, R), 0.0), specHighlight);
	
	
//from prev
   //vec4 textureColor = texture( textureSampler, vertexUV );
   //FragColor = textureColor;

   //Calculate shadow
   float shadow;
   if(enableShadow == 1) {
	shadow = shadowCalc(dot(lightDirectionCam, normCam));
   } else {
	shadow = 0;
   }

   vec3 finalColor = 
   matAmbientColor + 
   (1.0f - shadow) *
   (matDiffuseColor * lightColor * lightPower * cosTheta / (distance * distance)
   + matSpecColor * lightColor * cosAlpha * specStrength);

   FragColor = vec4(finalColor, 1.0f);
}
