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
	
	GLuint id;	
	glGenTextures(1, &id);
	
	std::vector<unsigned char> buffer, image;
	LodePNG::loadFile(buffer, "objects/textures/" + m_textureFile);
	LodePNG::Decoder decoder;
	decoder.decode(image, buffer.empty() ? 0 : &buffer[0], (unsigned)buffer.size());

	//
	// Flip and invert the PNG image since OpenGL likes to load everything
	// backwards from what is considered normal!
	//

	unsigned char *imagePtr = &image[0];
	int halfTheHeightInPixels = decoder.getHeight() / 2;
	int heightInPixels = decoder.getHeight();

	// Assuming RGBA for 4 components per pixel.
	int numColorComponents = 4;

	// Assuming each color component is an unsigned char.
	int widthInChars = decoder.getWidth() * numColorComponents;

	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;

	for( int h = 0; h < halfTheHeightInPixels; ++h )
	{
	    top = imagePtr + h * widthInChars;
	    bottom = imagePtr + (heightInPixels - h - 1) * widthInChars;

	    for( int w = 0; w < widthInChars; ++w )
	    {
	        // Swap the chars around.
	        temp = *top;
	        *top = *bottom;
	        *bottom = temp;

	        ++top;
	        ++bottom;
	    }
	}
    
	glBindTexture(GL_TEXTURE_2D, id);

	int textureWrap = GL_REPEAT;
	if (m_clamping)
		textureWrap = GL_CLAMP_TO_EDGE;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, decoder.getWidth(), decoder.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	
	m_textureID = id;
	texturesIDs[m_textureFile] = id;
}

void Material::apply() {
	if (lastApplied != this) {	
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	
		glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
	
	    glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	
	lastApplied = this;
}