#ifndef VERTEX_HEADER
#define VERTEX_HEADER

class Vertex {

public:

	Vertex() : X(0), Y(0), Z(0), W(0) { };

	//Contructor
	Vertex(double x, double y, double z, double w)
		: X(x), Y(y), Z(z), W(w) { };

	//DATA MEMBERS
	double X;
	double Y;
	double Z;
	double W;

private:
	
};

#endif