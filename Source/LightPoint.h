#pragma once
#include "Light.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

class LightPoint : public Light {
public:
	LightPoint(vec3 pos, vec3 color);
	void setPosition(vec3 pos);
private:
	void setShaderLocation();
	void setLightMatrix();
};