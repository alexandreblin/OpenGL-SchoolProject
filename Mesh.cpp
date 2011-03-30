#include "Mesh.h"

using namespace std;

Mesh::Mesh(std::string filename, Point pos, Angle angle, Vector scale) : Object(pos, angle, scale), m_disableMaterial(false) {
	loadFromFile(filename);
	
	computeFaceNormals();
	computeRemainingNormals();
	
    loadTextures();
    
    scaleVertices(m_scale);
}

void Mesh::draw(bool keepMatrix) {
    if (!keepMatrix)
        glPushMatrix();
    
	glTranslatef(m_position.x(), m_position.y(), m_position.z());
	
	glRotatef(m_angle.pitch(), 1, 0, 0);
	glRotatef(m_angle.yaw(), 0, 1, 0);
	glRotatef(m_angle.roll(), 0, 0, 1);
	
	for (unsigned int i = 0; i < m_faces.size(); ++i) {		
		Face & f = m_faces[i];
		
		if (!m_disableMaterial)
		    f.material()->apply();

		glBegin(GL_POLYGON);
		
		for (unsigned int j = 0; j < f.numVertices(); ++j) {
			Point & vertex = m_vertices[f.vertices()[j]];
			Point & normal = m_vertexNormals[f.normals()[j]];
			
			if (f.hasTexCoords()) {
				std::vector<float> & texCoords = m_texCoords[f.texCoords()[j]];
				glTexCoord2f(texCoords[0], texCoords[1]);
			}
			
			glNormal3f(normal.x(), normal.y(), normal.z());
			glVertex3f(vertex.x(), vertex.y(), vertex.z());
		}
		
		glEnd();
	}
	
	if (!keepMatrix)
        glPopMatrix();
}

void Mesh::computeRemainingNormals() {
	cout << "Computing remaining vertex normals..." << endl;
	int count = 0;
	// on boucle sur chaque face de l'objet
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		Face & face = m_faces[i];
		
		if (face.hasNormals()) continue;

		count++;
		
		//if (count % 1000 == 0)
		//	cout << count << "/" << m_faces.size() << endl;
		
		// on boucle sur chaque sommet de la face
		for (unsigned int j = 0; j < face.vertices().size(); ++j) {
			Vector normal(0, 0, 0);
			
			for (unsigned int k = 0; k < m_faces.size(); k++) {
				if (find(m_faces[k].vertices().begin(), m_faces[k].vertices().end(), face.vertices()[j]) != m_faces[k].vertices().end()) {
					// si la face contient notre sommet, on ajoute sa normale
					normal += m_faceNormals[k];
				}
			}
			
			m_vertexNormals.push_back(normal.normalized());
			face.normals().push_back(m_vertexNormals.size()-1);
		}		
	}

	cout << count << " remaining vertex normals computed!" << endl;
}

void Mesh::computeFaceNormals() {
	// inspiré de http://www.opengl.org/wiki/Calculating_a_Surface_Normal (Newell's method)
	// pour pouvoir calculer la normale de la face quelque soit son nombre de sommets
	
	if (m_faceNormals.size() != m_faces.size()) {
		cout << "Computing face normals..." << endl;
		
		m_faceNormals.clear();
		
		for (unsigned int i = 0; i < m_faces.size(); ++i) {
			// on boucle sur chaque face
			
			//cout << i+1 << "/" << m_faces.size() << endl;
			
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

Point Mesh::getFaceCenter(Face f) {
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

void Mesh::setDisableMaterial(bool b) {
    m_disableMaterial = b;
}

void Mesh::setMaterial(Material *m) {
    for (unsigned int i = 0; i < m_faces.size(); ++i) {
        m_faces[i].setMaterial(m);
    }
}

void Mesh::scaleVertices(Vector scale) {
    for (unsigned int i = 0; i < m_vertices.size(); ++i) {
        m_vertices[i].setX(m_vertices[i].x() * scale.x());
        m_vertices[i].setY(m_vertices[i].y() * scale.y());
        m_vertices[i].setZ(m_vertices[i].z() * scale.z());
    }
}

void Mesh::loadFromFile(std::string filename) {
	ifstream file(filename.c_str());
	
	Material *defaultMat = new Material();
	Material *currentMat = defaultMat;
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		str >> type;

		if (type == "v" || type == "vn") {
			float x, y, z;
			
			str >> x >> y >> z;
			
			if (type == "v") {
				m_vertices.push_back(Point(x, y, z));
			}
			else if (type == "vn") {
				m_vertexNormals.push_back(Vector(x, y, z));
			}
		}
		else if (type == "vt") {
			float x, y;
			std::vector<float> coords;
			
			str >> x >> y;
			coords.push_back(x);
			coords.push_back(y);
			
			m_texCoords.push_back(coords);
		}
		else if (type == "f") {
			Face f;
			
			f.setMaterial(currentMat);
			
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
		else if (type == "mtllib") {
			string mtlFilename;
			str >> mtlFilename;
			
			// on ajoute le chemin du dossier de l'objet au chemin du fichier MTL
			// car le chemin du MTL est relatif à celui de l'objet
			size_t lastSlash = filename.rfind("/");
			if (lastSlash != string::npos) {
				mtlFilename.insert(0, filename.substr(0, lastSlash+1));
			}
			
			cout << "MTL Lib file: " << mtlFilename << endl;
			parseMTLFile(mtlFilename);
		}
		else if (type == "usemtl") {
			string mtl;
			if (str >> mtl)
				currentMat = m_materials[mtl];
			else
				currentMat = defaultMat;
		}
	}
	
	file.close();
}

void Mesh::parseMTLFile(std::string filename) {
	ifstream file(filename.c_str());
	
	string currentMaterial;
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		
		string type;	
		str >> type;
		
		if (type == "newmtl") {
			str >> currentMaterial;

			m_materials[currentMaterial] = new Material();
		}
		else if (type == "Ka" || type == "Kd" || type == "Ke" || type == "Ks") {
			float r, g, b;
			
			str >> r;
			if (str >> g) {
			 	str >> b;
			}
			else {
				g = r;
				b = r;
			}
			
			if (type == "Ka") {
				m_materials[currentMaterial]->setAmbient(r, g, b);
			}
			else if (type == "Kd") {
				m_materials[currentMaterial]->setDiffuse(r, g, b);
			}
			else if (type == "Ke") {
				m_materials[currentMaterial]->setEmission(r, g, b);
			}
			else if (type == "Ks") {
				m_materials[currentMaterial]->setSpecular(r, g, b);
			}
		}
		else if (type == "Ns") {
			float shininess;
			str >> shininess;
			m_materials[currentMaterial]->setShininess(shininess);
		}
		else if (type == "map_Ka") {
			string value;
			str >> value;
			
			// on vérifie si on a l'option -clamp on après map_Ka
			if (value == "-clamp") {
				str >> value;
				if (value == "on") {
					m_materials[currentMaterial]->setClamping(true);
				}
				
				str >> value;
			}
			
			// on ajoute le chemin du dossier du MTL au chemin du fichier texture
			// car le chemin de la texture est relatif à celui du MTL
			size_t lastSlash = filename.rfind("/");
			if (lastSlash != string::npos) {
				value.insert(0, filename.substr(0, lastSlash+1));
			}
			
			m_materials[currentMaterial]->setTextureFile(value);
		}
	}
	
	file.close();
}

void Mesh::loadTextures() {
	map<string, Material *>::iterator it;
	for (it = m_materials.begin(); it != m_materials.end(); it++) {
        it->second->loadTexture();
	}
}