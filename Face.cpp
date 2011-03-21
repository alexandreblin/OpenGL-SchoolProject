#include "Face.h"

Face::Face() : m_smoothingGroup(0) {}

std::vector<int> & Face::vertices() {
	return m_vertices;
}

std::vector<int> & Face::texCoords() {
	return m_texCoords;
}

std::vector<int> & Face::normals() {
	return m_normals;
}

void Face::setSmoothingGroup(int s) {
	if (s < 0)
		s = 0;
		
	m_smoothingGroup = s;
}

int Face::smoothingGroup() {
	return m_smoothingGroup;
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