//triangle class. Defined by three objects from class Vertex.
//Has color represented by instance of ColorDbl.
//Has normal stored as an instance of Direction.

#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"	

class Camera
{
public:
	//Constructor
	Camera(Vertex e1, Vertex e2);

	//Destructor
	~Camera();

	void render();

private:
};