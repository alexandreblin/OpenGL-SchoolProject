#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Material.h"

class Face {
private:
	std::vector<int> m_vertices;
	std::vector<float> m_texCoords;
	std::vector<int> m_normals;
	
	int m_smoothingGroup;
	
	Material *m_material;

public:
	Face();
	
	std::vector<int> & vertices();
	std::vector<float> & texCoords();
	std::vector<int> & normals();
	
	void setMaterial(Material *mat);
	Material * material();
	
	void setSmoothingGroup(int s);
	int smoothingGroup();
	
	bool hasTexCoords();
	bool hasNormals();
	unsigned int numVertices();
};

#endif