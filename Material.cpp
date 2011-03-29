#include "Material.h"

std::map<std::string, int> Material::texturesIDs;
Material * Material::lastApplied = NULL;

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
}

// FIXME: nettoyer cette méthode
void Material::loadTexture() {
	if (m_textureFile.empty())
		return;
	
	if (texturesIDs[m_textureFile] > 0) {
		m_textureID = texturesIDs[m_textureFile];
		return;
	}
	
	// je ne sais pas si je peux appeler cette fonction plusieurs fois mais je n'ai vu
	// aucune contre-indication dans la documentation
	GLuint id;
	glGenTextures(1, &id);
	
	// on charge la texture avec LodePNG
	std::vector<unsigned char> buffer, image;
	LodePNG::loadFile(buffer, m_textureFile);
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
    
	glBindTexture(GL_TEXTURE_2D, id);

	int textureWrap = GL_REPEAT;
	if (m_clamping)
		textureWrap = GL_CLAMP_TO_EDGE;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	
	m_textureID = id;
	texturesIDs[m_textureFile] = id;
}

void Material::apply() {
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