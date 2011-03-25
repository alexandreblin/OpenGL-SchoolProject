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
#include <map>
#include <sstream>
#include <fstream>

#include "Point.h"
#include "Vector.h"
#include "Angle.h"
#include "Face.h"
#include "Material.h"

#include "lodepng.h"

class Object {
private:
	Point m_position;
	Angle m_angle;
	Vector m_scale;
	
	std::vector<Point> m_vertices;
	std::vector<Face> m_faces;
	
	std::vector<Vector> m_faceNormals;
	std::vector<Vector> m_vertexNormals;
	
	std::vector<std::vector<float> > m_texCoords;
	
	std::map<std::string, Material *> m_materials;
		
public:
    Object(std::string filename, Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0), Vector scale = Vector(1, 1, 1));

	void draw();
	
	Point & position();
	Angle & angle();
	
	void loadTextures();
	
private:
	void loadFromFile(std::string filename);
	void parseMTLFile(std::string filename);
	
    void scaleVertices(Vector scale);
    
	void computeFaceNormals();
	void computeRemainingNormals();
	
	Point getFaceCenter(Face f);
};

#endif