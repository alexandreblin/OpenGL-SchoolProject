#include "Material.h"

Material::Material() : m_textureFile(), m_textureID(0) {
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

std::string Material::textureFile() {
	return m_textureFile;
}

void Material::setTextureFile(std::string file) {
	m_textureFile = file;
}

int Material::textureID() {
    return m_textureID;
}

void Material::setTextureID(int id) {
    m_textureID = id;
}

void Material::apply() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	
    glBindTexture(GL_TEXTURE_2D, textureID());
}