#pragma once

#include <glm.hpp>

#include "Triangle.h"
#include "ColorDbl.h"

class AreaLight {
public:

	// AREA LIGHT
	AreaLight(Triangle a, float i, ColorDbl c) : area(a), color(c), intensity(i) {};

	float intensity;
	ColorDbl color;
	Triangle area;
private:

};
