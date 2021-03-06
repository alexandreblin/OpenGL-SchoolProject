#ifndef MESH_H
#define MESH_H

#include "Object.h"

#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Face.h"
#include "Material.h"

class Mesh : public Object {
private:
	std::vector<Point> m_vertices;
	std::vector<Face> m_faces;
	
	std::vector<Vector> m_faceNormals;
	std::vector<Vector> m_vertexNormals;
	
	std::vector<std::vector<float> > m_texCoords;
	
	// tableau associant les noms des matériaux à leurs objets correspondants
	std::map<std::string, Material *> m_materials;
	
    bool m_disableMaterial;
		
public:
    Mesh(std::string filename, Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0));

	virtual void draw(bool keepMatrix = false);
	
    void setMaterial(Material *m);
	
private:
	void loadFromFile(std::string filename);
	void parseMTLFile(std::string filename);
    
	void computeFaceNormals();
	void computeRemainingNormals();
};

#endif
