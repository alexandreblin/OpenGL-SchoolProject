#include "Object.h"

using namespace std;

Object::Object(std::string filename, Point pos, Angle angle, Vector scale) : m_position(pos), m_angle(angle), m_scale(scale) {
	loadFromFile(filename);
	
	computeFaceNormals();
	computeVertexNormals();

	saveToFile(filename);

	scaleVertices(m_scale);
}

void Object::draw() {
	glTranslated(m_position.x(), m_position.y(), m_position.z());
	
	glRotated(-m_angle.pitch(), 1, 0, 0);
	glRotated(-m_angle.yaw(), 0, 1, 0);
	glRotated(-m_angle.roll(), 0, 0, 1);
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		glColor3d(0.5, 0.86, 0.27);
		
		Face f = m_faces[i];
		
		if (f.numVertices() == 3)
			glBegin(GL_TRIANGLES);
		else if (f.numVertices() == 4)
			glBegin(GL_QUADS);
		else if (f.numVertices() > 4)
			glBegin(GL_POLYGON);
		else {
			std::cout << "Invalid face " << i << std::endl;
			continue;
		}
		
		for (unsigned int j = 0; j < f.numVertices(); ++j) {
			Point vertex = m_vertices[f.vertices()[j]];
			Point normal = m_vertexNormals[f.vertices()[j]];
			
			glNormal3d(normal.x(), normal.y(), normal.z());
			glVertex3d(vertex.x(), vertex.y(), vertex.z());
		}
		
		glEnd();
	}
}

Point & Object::position() {
	return m_position;
}

Angle & Object::angle() {
	return m_angle;
}

void Object::computeFaceNormals() {
	// d'après http://www.opengl.org/wiki/Calculating_a_Surface_Normal
	
	if (m_faceNormals.size() != m_faces.size()) {
		cout << "Computing face normals..." << endl;
		
		m_faceNormals.clear();
		
		for (unsigned int i = 0; i < m_faces.size(); ++i) {
			// on boucle sur chaque face
			
			cout << i+1 << "/" << m_faces.size() << endl;
			
			Face face = m_faces[i];
			Vector normal(0, 0, 0);
		
			for (unsigned int j = 0; j < face.numVertices(); ++j) {
				// on boucle sur chaque sommet de la face
				Point curVertex = m_vertices[face.vertices()[j]];
				Point nextVertex = m_vertices[face.vertices()[(j+1)%face.numVertices()]];
			
				normal.addX((curVertex.y() - nextVertex.y()) * (curVertex.z() + nextVertex.z()));
				normal.addY((curVertex.z() - nextVertex.z()) * (curVertex.x() + nextVertex.x()));
				normal.addZ((curVertex.x() - nextVertex.x()) * (curVertex.y() + nextVertex.y()));
			}
		
			m_faceNormals.push_back(normal.normalized());
		}
		
		cout << "Face normals computed!" << endl;
	}
}

void Object::computeVertexNormals() {
	if (m_vertexNormals.size() != m_vertices.size()) {
		cout << "Computing vertex normals..." << endl;
		
		m_vertexNormals.clear();
		
		for (unsigned int i = 0; i < m_vertices.size(); ++i) {
			// on boucle sur chaque sommet de l'objet

			cout << i+1 << "/" << m_vertices.size() << endl;
		
			Vector normal(0, 0, 0);
		
			for (unsigned int j = 0; j < m_faces.size(); ++j) {
				// on boucle sur chaque face de l'objet
				Face face = m_faces[j];
				
				if (find(face.vertices().begin(), face.vertices().end(), i) != face.vertices().end()) {
					// si la face contient notre sommet, on ajoute sa normale
					normal += m_faceNormals[j];
				}
			}
			
			m_vertexNormals.push_back(normal.normalized());
		}

		cout << "Vertex normals computed!" << endl;
	}
}

Point Object::getFaceCenter(Face f) {
	Point center(0, 0, 0);
	
	int numVertices = f.numVertices();
	
	for (int i = 0; i < numVertices; ++i) {
		center.addX(m_vertices[f.vertices()[i]].x());
		center.addY(m_vertices[f.vertices()[i]].y());
		center.addZ(m_vertices[f.vertices()[i]].z());
	}
	
	center.setX(center.x() / numVertices);
	center.setY(center.y() / numVertices);
	center.setZ(center.z() / numVertices);
	
	return center;
}

void Object::scaleVertices(Vector scale) {
	for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		m_vertices[i].setX(m_vertices[i].x() * scale.x());
		m_vertices[i].setY(m_vertices[i].y() * scale.y());
		m_vertices[i].setZ(m_vertices[i].z() * scale.z());
	}
}

void Object::loadFromFile(std::string filename) {
	ifstream file(filename.c_str());
	
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		str >> type;

		if (type == "Vertex" || type == "Scale" || type == "FaceNormal" || type == "VertexNormal") {
			double x, y, z;
			
			str >> x >> y >> z;
			
			if (type == "Vertex") {
				m_vertices.push_back(Point(x, y, z));
			}
			else if (type == "FaceNormal") {
				m_faceNormals.push_back(Vector(x, y, z));
			}
			else if (type == "VertexNormal") {
				m_vertexNormals.push_back(Vector(x, y, z));
			}
			else if (type == "Scale") {
				m_scale = Vector(x, y, z);
			}
		}
		else if (type == "Face") {
			Face f;
			while (str.good()) {
				int num;
			
				if (str >> num)
					f.vertices().push_back(num-1);
			}
			
			m_faces.push_back(f);
		}
	}
	
	file.close();
}

void Object::saveToFile(std::string filename) {
	ofstream file(filename.c_str(), ios::trunc);
	
	file.precision(std::numeric_limits<double>::digits10);
	
	if (m_scale.x() != 1 || m_scale.y() != 1 || m_scale.z() != 1)
		file << "Scale " << m_scale << endl << endl;
	
	for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		file << "Vertex " << m_vertices[i] << endl;
	}
	
	file << endl;
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		file << "Face";
		
		Face f = m_faces[i];
		for (unsigned int j = 0; j < f.numVertices(); ++j)
			file << " " << f.vertices()[j]+1;
		
		file << endl;
	}
	
	file << endl << endl << "# Normales générées automatiquement" << endl << endl;
	
	for (unsigned int i = 0; i < m_faceNormals.size(); ++i) {
		file << "FaceNormal " << m_faceNormals[i] << endl;
	}
	
	file << endl;
	
	for (unsigned int i = 0; i < m_vertexNormals.size(); ++i) {
		file << "VertexNormal " << m_vertexNormals[i] << endl;
	}
		
	file.close();
}
