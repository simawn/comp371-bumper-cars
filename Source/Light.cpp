#include "Light.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
Light::Light() {}

Light::Light(vec3 pos) {
	position = pos;
}

vec3 Light::getPosition() {
	return position;
}

