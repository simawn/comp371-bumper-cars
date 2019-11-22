#pragma once
#include "Light.h"

using namespace glm;
using namespace std;

class LightSpot : public Light {
public:
	LightSpot(vec3 pos, vec3 color, vec3 direction, float cutOff, float outerCutOff);
};