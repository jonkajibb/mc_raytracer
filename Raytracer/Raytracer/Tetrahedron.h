//Class tetrahedron
//a wierd object lmao

#include "Vertex.h"

class Tetrahedron
{
public:

	Tetrahedron() : pos() { };

	Tetrahedron(Vertex v)
	{
		pos = v;

	};


	//data declarations
	Vertex pos;
	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vertex v3;


private:

};