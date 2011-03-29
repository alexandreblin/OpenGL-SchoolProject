#ifndef MATERIAL_H
#define MATERIAL_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>
#include <map>
#include <string>

#include "lodepng.h"

class Material {
private:
	float m_ambient[3];
	float m_diffuse[3];
	float m_specular[3];
	float m_emission[3];
	float m_shininess;
	bool m_clamping;
	
	static std::map<std::string, int> texturesIDs;
	static Material * lastApplied;
	
	std::string m_textureFile;
    int m_textureID;
	
public:
		
	Material();
	
	float * ambient();
	float * diffuse();
	float * specular();
	float shininess();
	
	void setAmbient(float r, float g, float b);
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setEmission(float r, float g, float b);
	void setShininess(float s);
	void setClamping(bool clamping);
	
	std::string textureFile();
	void setTextureFile(std::string file);

	void loadTexture();
	
	void apply();
};

#endif