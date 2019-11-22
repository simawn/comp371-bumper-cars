#include "LightSpot.h"

LightSpot::LightSpot(vec3 pos, vec3 color, vec3 direction, float cutOff, float outerCutOff) :
	Light(pos, color, direction, cutOff, outerCutOff) {

	spotLights.push_back(this);
}