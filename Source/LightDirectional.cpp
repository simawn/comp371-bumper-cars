#include "LightDirectional.h"

LightDirectional::LightDirectional(vec3 pos, vec3 color, vec3 direction) : Light(pos, color, direction) {
	directionalLights.push_back(this);
}