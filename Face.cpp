#include "Face.h"

Face::Face() {}

std::vector<int> & Face::vertices() {
	return m_vertices;
}

std::vector<int> & Face::texCoords() {
	return m_texCoords;
}

std::vector<int> & Face::normals() {
	return m_normals;
}

unsigned int Face::numVertices() {
	return m_vertices.size();
}