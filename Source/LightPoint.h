#pragma once
#include "Light.h"

class LightPoint : public Light {
public:
	LightPoint(vec3 pos);
	void setPosition(vec3 pos);
private:
	void setShaderLocation();
};