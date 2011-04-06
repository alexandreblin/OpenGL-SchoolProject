#include "Material.h"

using namespace std;

Material * Material::lastApplied = NULL;
std::vector<Material *> Material::toLoad;
std::vector<Material *> Material::materials;

Material::Material() : m_shininess(0), m_clamping(false), m_textureFile(), m_textureID(0) {
	// valeurs par défaut
	// http://www.opengl.org/sdk/docs/man/xhtml/glMaterial.xml
	
	m_ambient[0] = 0.2;
	m_ambient[1] = 0.2;
	m_ambient[2] = 0.2;
	
	m_diffuse[0] = 0.8;
	m_diffuse[1] = 0.8;
	m_diffuse[2] = 0.8;

	m_specular[0] = 0;
	m_specular[1] = 0;
	m_specular[2] = 0;

	m_emission[0] = 0;
	m_emission[1] = 0;
	m_emission[2] = 0;
	
    materials.push_back(this);
}

Material::~Material() {
    glDeleteTextures(1, (GLuint *)&m_textureID);
}

void Material::deallocAll() {
    for (unsigned int i = 0; i < materials.size(); ++i)
        delete materials[i];
}

float * Material::ambient() {
	return m_ambient;
}

float * Material::diffuse() {
	return m_diffuse;
}

float * Material::specular() {
	return m_specular;
}

float Material::shininess() {
	return m_shininess;
}

void Material::setAmbient(float r, float g, float b) {
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
}

void Material::setDiffuse(float r, float g, float b) {
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
}

void Material::setSpecular(float r, float g, float b) {
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
}

void Material::setEmission(float r, float g, float b) {
	m_emission[0] = r;
	m_emission[1] = g;
	m_emission[2] = b;
}

void Material::setShininess(float s) {
	m_shininess = s;
}

void Material::setClamping(bool clamping) {
	m_clamping = clamping;
}

std::string Material::textureFile() {
	return m_textureFile;
}

void Material::setTextureFile(std::string file) {
	m_textureFile = file;
	
	// on ajoute le fichier dans la liste des textures à charger
    if (!m_textureFile.empty())
        toLoad.push_back(this);
}

// Méthode statique qui charge toutes les textures
void Material::loadTextures() {
    // tableau pour savoir l'ID d'une texture à partir de son
    // nom de fichier pour éviter de charger deux fois la même
    std::map<std::string, int> texturesIDs;
    
    // je compte le nombre de textures distinctes pour générer
    // exactement le bon nombre d'IDs de texture
    std::set<std::string> uniqueTextures;
    for (unsigned int i = 0; i < toLoad.size(); ++i)
        uniqueTextures.insert(toLoad[i]->m_textureFile);
    
    GLuint IDs[uniqueTextures.size()];
	glGenTextures(uniqueTextures.size(), IDs);
	
    int currentID = 0; 
    for (unsigned int i = 0; i < toLoad.size(); ++i) {
    	if (texturesIDs[toLoad[i]->m_textureFile] > 0) {
    	    // si on a déjà un ID pour cette texture, on passe à la prochaine
    		toLoad[i]->m_textureID = texturesIDs[toLoad[i]->m_textureFile];
    		continue;
    	}
	    
	    // code un peu barbare pour afficher le nom de la texture sans le dossier :P
        cout << "Loading texture " << toLoad[i]->m_textureFile.substr(toLoad[i]->m_textureFile.rfind("/") != string::npos ? toLoad[i]->m_textureFile.rfind("/")+1 : 0) << endl;

    	// on charge la texture avec LodePNG
    	std::vector<unsigned char> buffer, image;
    	LodePNG::loadFile(buffer, toLoad[i]->m_textureFile);
    	LodePNG::Decoder decoder;
    	decoder.decode(image, buffer.empty() ? 0 : &buffer[0], (unsigned)buffer.size());
	
        int height = decoder.getHeight();
        int width = decoder.getWidth();
    
        // on inverse la texture car OpenGL les charge à l'envers
        unsigned char tmp;
        for (int h = 0; h < height/2; ++h) {
            int line = h * (width*4);
            int oppositeLine = (height - h - 1) * (width*4);

            for (int w = 0; w < width*4; ++w) {
                tmp = image[line + w];
                image[line + w] = image[oppositeLine + w];
                image[oppositeLine + w] = tmp;
            }
        }
    
    	glBindTexture(GL_TEXTURE_2D, IDs[currentID]);

    	int textureWrap = GL_REPEAT;
    	if (toLoad[i]->m_clamping)
    		textureWrap = GL_CLAMP_TO_EDGE;
	
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	
	    // on stocke l'ID de la texture dans l'objet Material pour qu'elle puisse être appliquée plus tard
    	toLoad[i]->m_textureID = IDs[currentID];
    	
    	// on stocke l'ID et le nom du fichier correspondant dans textureIDs pour ne pas la recharger
    	// si elle est présente plus d'une fois dans le tableau
    	texturesIDs[toLoad[i]->m_textureFile] = IDs[currentID];
    	
        currentID++;
	}
	
    toLoad.clear();
}

void Material::apply() {
    if (!Material::toLoad.empty()) {
        Material::loadTextures();
    }
	if (lastApplied != this) {	
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, m_emission);
	
		glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
	
	    glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	
	lastApplied = this;
}
