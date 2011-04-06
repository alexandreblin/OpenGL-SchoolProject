#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Material.h"

class Face {
private:
	std::vector<int> m_vertices;
	std::vector<float> m_texCoords;
	std::vector<int> m_normals;
	
	Material *m_material;

public:
	Face();
	
	// tableaux contenant les indices des sommets/normales de la face
	// dans le tableau correspondant dans Mesh
	std::vector<int> & vertices();
	std::vector<int> & normals();
	
	// contient directement les coordonnées des textures
	std::vector<float> & texCoords();
	
	void setMaterial(Material *mat);
	Material * material();
	
	bool hasTexCoords();
	bool hasNormals();
	unsigned int numVertices();
};

#endif
