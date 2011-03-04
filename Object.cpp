#include "Object.h"

using namespace std;

Object::Object(std::string filename, Point pos, Vector axis, Vector scale) : m_position(pos), m_axis(axis), m_scale(scale) {
	loadFromFile(filename);
	
	computeFaceNormals();
	computeVertexNormals();
}

void Object::draw() {
	glScaled(m_scale.x(), m_scale.y(), m_scale.z());
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		glColor3d(0, 0, 1);
		
		Face f = m_faces[i];
		
		if (f.size() == 3)
			glBegin(GL_TRIANGLES);
		else if (f.size() == 4)
			glBegin(GL_QUADS);
		else if (f.size() > 4)
			glBegin(GL_POLYGON);
		else {
			std::cout << "Invalid face " << i << std::endl;
			continue;
		}
		
		for (unsigned int j = 0; j < f.size(); ++j) {
			Point vertex = m_vertices[f[j]];
			Point normal = m_vertexNormals[f[j]];
			
			glNormal3d(normal.x(), normal.y(), normal.z());
			glVertex3d(vertex.x(), vertex.y(), vertex.z());
		}
		
		glEnd();
		
		
		glBegin(GL_LINES);
		glColor3d(1, 0, 0);

		Point center = getFaceCenter(f);
		Point centerNormal = center + m_faceNormals[i];

		glVertex3dv((const GLdouble *)&center);
		glVertex3dv((const GLdouble *)&centerNormal);
		
		glEnd();
	}
	
	for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		glBegin(GL_LINES);
		
		glColor3d(0, 1, 0);
		
		Point vertex = m_vertices[i];
		Point normal = vertex + m_vertexNormals[i];
		
		glVertex3d(vertex.x(), vertex.y(), vertex.z());
		glVertex3d(normal.x(), normal.y(), normal.z());
		
		glEnd();
	}
}

void Object::computeFaceNormals() {
	// d'après http://www.opengl.org/wiki/Calculating_a_Surface_Normal
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		// on boucle sur chaque face
		Face face = m_faces[i];		
		Vector normal(0, 0, 0);
		
		for (unsigned int j = 0; j < face.size(); ++j) {
			// on boucle sur chaque sommet de la face
			Point curVertex = m_vertices[face[j]];
			Point nextVertex = m_vertices[face[(j+1)%face.size()]];
			
			normal.addX((curVertex.y() - nextVertex.y()) * (curVertex.z() + nextVertex.z()));
			normal.addY((curVertex.z() - nextVertex.z()) * (curVertex.x() + nextVertex.x()));
			normal.addZ((curVertex.x() - nextVertex.x()) * (curVertex.y() + nextVertex.y()));
		}
		
		m_faceNormals.push_back(normal.normalized());
	}
}

void Object::computeVertexNormals() {
	for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		// on boucle sur chaque sommet de l'objet
		
		Vector normal(0, 0, 0);
		
		for (unsigned int j = 0; j < m_faces.size(); ++j) {
			// on boucle sur chaque face de l'objet
			
			Face face = m_faces[j];
			if (find(face.begin(), face.end(), i) != face.end()) {
				// si la face contient notre sommet, on ajoute sa normale
				normal += m_faceNormals[j];
			}
		}
		
		m_vertexNormals.push_back(normal.normalized());
	}
}

Point Object::getFaceCenter(Face f) {
	Point center(0, 0, 0);
	
	int numFaces = f.size();
	
	for (int i = 0; i < numFaces; ++i) {
		center.addX(m_vertices[f[i]].x());
		center.addY(m_vertices[f[i]].y());
		center.addZ(m_vertices[f[i]].z());
	}
	
	center.setX(center.x() / numFaces);
	center.setY(center.y() / numFaces);
	center.setZ(center.z() / numFaces);
	
	return center;
}

void Object::loadFromFile(std::string filename) {
	ifstream file(filename.c_str());
	
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		str >> type;

		if (type == "Vertex" || type == "Scale") {
			double x, y, z;
			
			str >> x >> y >> z;
			
			if (type == "Vertex") {
				m_vertices.push_back(Point(x, y, z));
			}
			else if (type == "Scale") {
				m_scale = Vector(x, y, z);
			}
		}
		else if (type == "Face") {
			Face f;
			while (str.good()) {
				int num;
			
				str >> num;
				
				// on soustrait 1 car dans le fichier la numérotation commence à 1
				// et les tableaux sont indexés à partir de 0
				f.push_back(num-1);
			}
			
			m_faces.push_back(f);
		}
	}
}
