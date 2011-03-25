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
#include <string>

class Material {
private:
	float m_ambient[3];
	float m_diffuse[3];
	float m_specular[3];
	
	std::string m_textureFile;
    int m_textureID;
	
public:
	Material();
	
	float * ambient();
	float * diffuse();
	float * specular();
	
	void setAmbient(float r, float g, float b);
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	
	std::string textureFile();
	void setTextureFile(std::string file);
	
    int textureID();
    void setTextureID(int id);
	
	void apply();
};

#endif