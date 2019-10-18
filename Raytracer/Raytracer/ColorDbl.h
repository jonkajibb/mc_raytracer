#ifndef COLORDBL_HEADER
#define COLORDBL_HEADER

#include <algorithm>

//Contains RGB values
class ColorDbl {
public:
	ColorDbl() : R(0), G(0), B(0) { };
	//Constructor
	ColorDbl(double r, double g, double b) : R(r), G(g), B(b) {};

	ColorDbl operator*(double const num) {
		double x = num;
		if (x > 1) {
			x = 1;
		}
		else if (x < 0) {
			x = 0;
		}
		return ColorDbl(R*x, G*x, B*x);
	};

	ColorDbl operator*(ColorDbl &c1) {
		c1.R = c1.R / 255;
		c1.G = c1.G / 255;
		c1.B = c1.B / 255;
		return ColorDbl(this->R*c1.R, this->G*c1.G, this->B*c1.B);
	};

	//ColorDbl shading(Ray &importance, Triangle hitTri, Scene s);

	double R;
	double G;
	double B;
private:

	//friend std::
};

#endif
