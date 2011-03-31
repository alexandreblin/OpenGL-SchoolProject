#include "Mesh.h"

using namespace std;

Mesh::Mesh(std::string filename, Point pos, Angle angle) : Object(pos, angle), m_disableMaterial(false) {
	loadFromFile(filename);
	
	computeFaceNormals();
	
	computeRemainingNormals();
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
		
		if (f.material() != NULL)
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

// méthode calculant les normales aux sommets manquantes (car non précisées dans le fichier OBJ)
void Mesh::computeRemainingNormals() {
	// on boucle sur chaque face de l'objet
	for (unsigned int i = 0; i < m_faces.size(); ++i) {
		Face & face = m_faces[i];
		
		if (face.hasNormals()) continue;
		
		// on boucle sur chaque sommet de la face
		for (unsigned int j = 0; j < face.vertices().size(); ++j) {
			Vector normal(0, 0, 0);
			
			for (unsigned int k = 0; k < m_faces.size(); k++) {
				if (find(m_faces[k].vertices().begin(), m_faces[k].vertices().end(), face.vertices()[j]) != m_faces[k].vertices().end()) {
					// si la face contient notre sommet, on ajoute sa normale
					normal += m_faceNormals[k];
				}
			}
			
			// on ajoute le vecteur dans le tableau
			m_vertexNormals.push_back(normal.normalized());
			
			// on stocke son indice dans l'objet Face
			face.normals().push_back(m_vertexNormals.size()-1);
		}		
	}
}

void Mesh::computeFaceNormals() {
	// inspiré de http://www.opengl.org/wiki/Calculating_a_Surface_Normal (Newell's method)
	// pour pouvoir calculer la normale de la face quelque soit son nombre de sommets
	// (j'aurais pu faire moi même l'algo mais vu que celui-ci était sur le wiki d'OpenGL je pense qu'il est plus sûr)
	
	if (m_faceNormals.size() != m_faces.size()) {
		m_faceNormals.clear();
		
		for (unsigned int i = 0; i < m_faces.size(); ++i) {
			// on boucle sur chaque face			
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
	}
}

void Mesh::setMaterial(Material *m) {
    for (unsigned int i = 0; i < m_faces.size(); ++i) {
        m_faces[i].setMaterial(m);
    }
}

// Méthode qui parse les fichiers OBJ
void Mesh::loadFromFile(std::string filename) {
	ifstream file(filename.c_str());
	
    std::cout << "Loading object " << filename.substr(filename.rfind("/") != string::npos ? filename.rfind("/")+1 : 0) << std::endl;
	
	Material *currentMat = NULL;
	
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		// on récupère le premier mot de la ligne pour savoir quel type de données on va parser
		str >> type;

		if (type == "v" || type == "vn") { // vecteur ou normale
			float x, y, z;
			
			str >> x >> y >> z;
			
			if (type == "v") {
				m_vertices.push_back(Point(x, y, z));
			}
			else if (type == "vn") {
				m_vertexNormals.push_back(Vector(x, y, z));
			}
		}
		else if (type == "vt") { // coordonnées de texture
			float x, y;
			std::vector<float> coords;
			
			str >> x >> y;
			coords.push_back(x);
			coords.push_back(y);
			
			m_texCoords.push_back(coords);
		}
		else if (type == "f") { // face
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
		else if (type == "mtllib") { // définition du fichier .mtl
			string mtlFilename;
			str >> mtlFilename;
			
			// on ajoute le chemin du dossier de l'objet au chemin du fichier MTL
			// car le chemin du MTL est relatif à celui de l'objet
			size_t lastSlash = filename.rfind("/");
			if (lastSlash != string::npos) {
				mtlFilename.insert(0, filename.substr(0, lastSlash+1));
			}
			
			parseMTLFile(mtlFilename);
		}
		else if (type == "usemtl") { // définition du matériau courant
			string mtl;
			if (str >> mtl)
				currentMat = m_materials[mtl];
			else
				currentMat = NULL;
		}
	}
	
	file.close();
}

// Méthode qui parse les fichiers MTL, appelée lorsque l'on rencontre un "mtllib" dans loadFromFile()
void Mesh::parseMTLFile(std::string filename) {
	ifstream file(filename.c_str());
	
	string currentMaterial;
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		
		string type;	
		str >> type;
		
		if (type == "newmtl") { // définition d'un nouveau matériau
			str >> currentMaterial;

			m_materials[currentMaterial] = new Material();
		}
		else if (type == "Ka" || type == "Kd" || type == "Ke" || type == "Ks") { // une couleur
			float r, g, b;
			
			str >> r;
			if (str >> g) {
			 	str >> b;
			}
			else {
				g = r;
				b = r;
			}
			
			if (type == "Ka") { // ambient
				m_materials[currentMaterial]->setAmbient(r, g, b);
			}
			else if (type == "Kd") { // diffuse
				m_materials[currentMaterial]->setDiffuse(r, g, b);
			}
			else if (type == "Ke") { // emission (pas sûr que ça soit dans le standard OBJ mais certains fichiers contiennent ce mot-clé)
				m_materials[currentMaterial]->setEmission(r, g, b);
			}
			else if (type == "Ks") { // spéculaire
				m_materials[currentMaterial]->setSpecular(r, g, b);
			}
		}
		else if (type == "Ns") { // brillance
			float shininess;
			str >> shininess;
			m_materials[currentMaterial]->setShininess(shininess);
		}
		else if (type == "map_Ka") { // fichier de texture
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