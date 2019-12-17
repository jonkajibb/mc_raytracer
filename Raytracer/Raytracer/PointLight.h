#pragma once

#include <glm.hpp>

#include "Vertex.h"
#include "ColorDbl.h"

class PointLight {
public:
	PointLight() {
	//	pos;
		intensity = 0;
	//	color;
	}

	// POINT LIGHT
	PointLight(glm::vec4 p, float i, ColorDbl c) : pos(p), intensity(i), color(c) {};
	
	glm::vec4 pos;
	float intensity;
	ColorDbl color;
private:

};
