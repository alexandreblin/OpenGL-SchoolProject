#ifndef OBJECT_H
#define OBJECT_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>
#include <sstream>
#include <fstream>

#include "Point.h"
#include "Vector.h"

typedef std::vector<int> Face;

class Object {
private:
	Point m_position;
	Vector m_axis;
	
	std::vector<Point> m_vertices;
	std::vector<Face> m_faces;
	
	std::vector<Vector> m_faceNormals;
	std::vector<Vector> m_vertexNormals;
		
public:
    Object(std::string filename, Point pos = Point(0, 0, 0), Vector axis = Vector(0, 1, 0));

	void draw();
	
private:
	void loadFromFile(std::string filename);
	void computeFaceNormals();
	void computeVertexNormals();
	
	Point getFaceCenter(Face f);
};

#endif