#ifndef VERTEX_HEADER
#define VERTEX_HEADER

class Vertex {

public:

	Vertex() : X(0), Y(0), Z(0), W(0) { };

	//Contructor
	Vertex(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w) { };

	//DATA MEMBERS
	float X;
	float Y;
	float Z;
	float W;

private:
	
};

#endif