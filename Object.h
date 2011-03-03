#ifndef OBJECT_H
#define OBJECT_H

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
	
public:
    Object(std::string filename, Point pos = Point(0, 0, 0), Vector axis = Vector(0, 1, 0));
};

#endif