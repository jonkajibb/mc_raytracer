#pragma once

#include <glm.hpp>

#include "Vertex.h"
#include "ColorDbl.h"

class Light {
public:
	Light() {
	//	pos;
		intensity = 0;
	//	color;
	}

	// POINT LIGHT
	Light(glm::vec4 p, float i, ColorDbl c) : pos(p), intensity(i), color(c) {};
	// AREA LIGHT
	Light(Triangle area, float i, ColorDbl col) : areaLight(area), color(col), intensity(i) {};
	
	glm::vec4 pos;
	float intensity;
	ColorDbl color;
	Triangle areaLight;
private:

};
