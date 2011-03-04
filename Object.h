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
#include "Angle.h"

typedef std::vector<int> Face;

class Object {
private:
	Point m_position;
	Angle m_angle;
	Vector m_scale;
	
	std::vector<Point> m_vertices;
	std::vector<Face> m_faces;
	
	std::vector<Vector> m_faceNormals;
	std::vector<Vector> m_vertexNormals;
	
	bool m_showNormals;
		
public:
    Object(std::string filename, Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0), Vector scale = Vector(1, 1, 1));

	void draw();
	
	Point & position();
	Angle & angle();
	
	void setShowNormals(bool visible);
	
private:
	void loadFromFile(std::string filename);
	void saveToFile(std::string filename);
	void scaleVertices(Vector scale);
	void computeFaceNormals();
	void computeVertexNormals();
	
	Point getFaceCenter(Face f);
};

#endif