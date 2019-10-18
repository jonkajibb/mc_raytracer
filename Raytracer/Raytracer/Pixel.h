#include "ColorDbl.h"

class Pixel
{
public:
	Pixel() : color(0, 0, 0) {};

	Pixel(ColorDbl c) : color(c) {};

	ColorDbl color;

};