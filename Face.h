#ifndef FACE_H
#define FACE_H

#include <vector>

class Face {
private:
	std::vector<int> m_vertices;
	std::vector<int> m_texCoords;
	std::vector<int> m_normals;
	
	int m_smoothingGroup;

public:
	Face();
	
	std::vector<int> & vertices();
	std::vector<int> & texCoords();
	std::vector<int> & normals();
	
	void setSmoothingGroup(int s);
	int smoothingGroup();
	
	bool hasTexCoords();
	bool hasNormals();
	unsigned int numVertices();
};

#endif