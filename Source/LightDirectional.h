#pragma once
#include "Light.h"

using namespace glm;
using namespace std;

class LightDirectional : public Light {
public:
	LightDirectional (vec3 pos, vec3 color, vec3 direction);
};