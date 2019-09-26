#ifndef COLORDBL_HEADER
#define COLORDBL_HEADER

//Contains RGB values
class ColorDbl {
public:
	ColorDbl() : R(0), G(0), B(0) { };
	//Constructor
	ColorDbl(double r, double g, double b) : R(r), G(g), B(b) {};

	double R;
	double G;
	double B;
private:

	//friend std::
};

#endif