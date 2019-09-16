#include "Triangle.h"

/* Constructor: initialize a TriangleSoup object to an empty object */
Triangle::Triangle() {
}


/* Destructor: clean up allocated data in a TriangleSoup object */
Triangle::~Triangle() {
	clean();
};

/* Clean up, remembering to de-allocate arrays and GL resources */
void Triangle::clean() {
	/*
	if (glIsVertexArray(vao)) {
		glDeleteVertexArrays(1, &vao);
	}
	vao = 0;

	if (glIsBuffer(vertexbuffer)) {
		glDeleteBuffers(1, &vertexbuffer);
	}
	vertexbuffer = 0;

	if (glIsBuffer(indexbuffer)) {
		glDeleteBuffers(1, &indexbuffer);
	}
	indexbuffer = 0;

	if (vertexarray) {
		delete[] vertexarray;
		vertexarray = NULL;
	}
	if (indexarray) {
		delete[] indexarray;
		indexarray = NULL;
	}
	nverts = 0;
	ntris = 0;
	*/
}


/* Create a demo object with a single triangle */
void Triangle::createTriangle() {

};

/* Print data from a TriangleSoup object, for debugging purposes */
void Triangle::print() {
	int i;

	printf("TriangleSoup vertex data:\n\n");
	for (i = 0; i < nverts; i++) {
		printf("%d: %8.2f %8.2f %8.2f\n", i,
			vertexarray[8 * i], vertexarray[8 * i + 1], vertexarray[8 * i + 2]);
	}
	printf("\nTriangleSoup face index data:\n\n");
	for (i = 0; i < ntris; i++) {
		printf("%d: %d %d %d\n", i,
			indexarray[3 * i], indexarray[3 * i + 1], indexarray[3 * i + 2]);
	}
};

/* Print information about a TriangleSoup object (stats and extents) */
void Triangle::printInfo() {
	int i;
	float x, y, z, xmin, xmax, ymin, ymax, zmin, zmax;

	printf("TriangleSoup infqormation:\n");
	printf("vertices : %d\n", nverts);
	printf("triangles: %d\n", ntris);
	xmin = xmax = vertexarray[0];
	ymin = ymax = vertexarray[1];
	zmin = zmax = vertexarray[2];
	for (i = 1; i < nverts; i++) {
		x = vertexarray[8 * i];
		y = vertexarray[8 * i + 1];
		z = vertexarray[8 * i + 2];
		//         printf("x y z : %8.2f %8.2f %8.2f\n", x, y, z);
		if (x < xmin) xmin = x;
		if (x > xmax) xmax = x;
		if (y < ymin) ymin = y;
		if (y > ymax) ymax = y;
		if (z < zmin) zmin = z;
		if (z > zmax) zmax = z;
	}
	printf("xmin: %8.2f\n", xmin);
	printf("xmax: %8.2f\n", xmax);
	printf("ymin: %8.2f\n", ymin);
	printf("ymax: %8.2f\n", ymax);
	printf("zmin: %8.2f\n", zmin);
	printf("zmax: %8.2f\n", zmax);
};

/* Render the geometry in a TriangleSoup object */
void TriangleSoup::render() {

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);

};

/*
 * private
 * printError() - Signal an error.
 * Simple printf() to console for portability.
 */
void TriangleSoup::printError(const char *errtype, const char *errmsg) {
	fprintf(stderr, "%s: %s\n", errtype, errmsg);
};