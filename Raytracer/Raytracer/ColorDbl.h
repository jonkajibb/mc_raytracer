#ifndef COLORDBL_HEADER
#define COLORDBL_HEADER

#include <algorithm>

//Contains RGB values
class ColorDbl {
public:
	ColorDbl() : R(0), G(0), B(0) { };
	//Constructor
	ColorDbl(float r, float g, float b) : R(r), G(g), B(b) {};

	ColorDbl operator*(float const num) {
		float x = num;
		if (x > 1) {
			x = 1;
		}
		else if (x < 0) {
			x = 0;
		}
		return ColorDbl(R*x, G*x, B*x);
	};

	ColorDbl operator/(float const num) {
		float x = num;
		if (x > 1) {
			x = 1;
		}
		else if (x < 0) {
			x = 0;
		}
		return ColorDbl(R/x, G/x, B/x);
	};

	ColorDbl operator*(ColorDbl &c1) {
		c1.R = c1.R / 255.0f;
		c1.G = c1.G / 255.0f;
		c1.B = c1.B / 255.0f;
		return ColorDbl(this->R*c1.R, this->G*c1.G, this->B*c1.B);
	};

	ColorDbl operator+(ColorDbl c1) {
		float x = (R + c1.R) / 2.0f;
		float y = (G + c1.G) / 2.0f;
		float z = (B + c1.B) / 2.0f;
		return ColorDbl(x, y, z);
	};

	//ColorDbl shading(Ray &importance, Triangle hitTri, Scene s);

	float R;
	float G;
	float B;
private:

	//friend std::
};

#endif