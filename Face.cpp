#include "Face.h"

Face::Face() : m_material(NULL) {}

std::vector<int> & Face::vertices() {
	return m_vertices;
}

std::vector<float> & Face::texCoords() {
	return m_texCoords;
}

std::vector<int> & Face::normals() {
	return m_normals;
}

void Face::setMaterial(Material *mat) {
    if (mat == NULL)
        mat = new Material(); // création d'un matériau par défaut si aucun n'est précisé
    
	m_material = mat;
}

Material * Face::material() {
	return m_material;
}

bool Face::hasTexCoords() {
	return (m_texCoords.size() == m_vertices.size());
}
bool Face::hasNormals() {
	return (m_normals.size() == m_vertices.size());
}

unsigned int Face::numVertices() {
	return m_vertices.size();
}