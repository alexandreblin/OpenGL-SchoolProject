#include "Object.h"

using namespace std;

Object::Object(std::string filename, Point pos, Angle angle) : m_position(pos), m_angle(angle) {
	loadFromFile(filename);
	
	computeFaceNormals();
	computeRemainingNormals();
	//computeVertexNormals();
	
	/*for (unsigned int i = 0; i < m_vertices.size(); ++i) {
		m_vertices[i].setX(m_vertices[i].x() * 0.01);
		m_vertices[i].setY(m_vertices[i].y() * 0.01);
		m_vertices[i].setZ(m_vertices[i].z() * 0.01);
	}*/
}

void Object::draw() {
	glTranslated(m_position.x(), m_position.y(), m_position.z());
	
	glRotated(-m_angle.pitch(), 1, 0, 0);
	glRotated(-m_angle.yaw(), 0, 1, 0);
	glRotated(-m_angle.roll(), 0, 0, 1);
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		glColor3d(0, 0, 1);
		
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
			Point normal = m_vertexNormals[f.normals()[j]];
			
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

void Object::computeRemainingNormals() {
	cout << "Computing remaining vertex normals..." << endl;
	int count = 0;
	// on boucle sur chaque face de l'objet
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		Face face = m_faces[i];
		
		if (face.hasNormals()) continue;

		count++;
		
		// on boucle sur chaque sommet de la face
		for (unsigned int j = 0; j < face.vertices().size(); ++j) {
			Vector normal(0, 0, 0);
			
			for (unsigned int k = 0; k < m_faces.size(); k++) {
				if (m_faces[k].smoothingGroup() == face.smoothingGroup() &&
				find(m_faces[k].vertices().begin(), m_faces[k].vertices().end(), face.vertices()[j]) != m_faces[k].vertices().end()) {
					// si la face contient notre sommet, on ajoute sa normale
					normal += m_faceNormals[k];
				}
			}
			
			m_vertexNormals.push_back(normal);
			face.normals().push_back(m_vertexNormals.size()-1);
		}		
	}

	cout << count << " remaining vertex normals computed!" << endl;
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

void Object::loadFromFile(std::string filename) {
	ifstream file(filename.c_str());
	
	int currentSmoothingGroup = 0;
	
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		str >> type;

		if (type == "v" || type == "vn") {
			double x, y, z;
			
			str >> x >> y >> z;
			
			if (type == "v") {
				m_vertices.push_back(Point(x, y, z));
			}
			else if (type == "vn") {
				m_vertexNormals.push_back(Vector(x, y, z));
			}
		}
		else if (type == "f") {
			Face f;
			
			f.setSmoothingGroup(currentSmoothingGroup);
			
			// format : f v/vt/vn, avec vt et vn optionnels
			while (str.good()) {
				int v, vt = -1, vn = -1;
			
				if (str >> v) {
					f.vertices().push_back(v-1); // on retire 1 car les numéros commencent à 1 dans le fichier et les tableaux sont indexés à 0
					
					// si on a un slash, on tente de lire vt
					if (str.peek() == 47) {
						str.seekg(1, ios_base::cur); // saute le slash
						
						// si on a pas un deuxième slash juste après, c'est que vt est bien là
						if (str.peek() != 47) {
							str >> vt;
							f.texCoords().push_back(vt-1);
						}
						
						// on vérifie si on a un deuxième slash
						if (str.peek() == 47) {
							str.seekg(1, ios_base::cur);
							str >> vn;
							f.normals().push_back(vn-1);
						}
					}
				}
			}
			
			m_faces.push_back(f);
		}
		else if (type == "s") {
			int s;
			if (str >> s)
				currentSmoothingGroup = s;
			else
				currentSmoothingGroup = 0;
		}
		else if (type == "mtllib") {
			string file;
			str >> file;
			cout << "MTL Lib file: " << file << endl;
		}
	}
	
	file.close();
}
