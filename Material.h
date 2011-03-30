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
#include <set>
#include <string>
#include <iostream>

#include "lodepng.h"

class Material {
private:
	float m_ambient[3];
	float m_diffuse[3];
	float m_specular[3];
	float m_emission[3];
	float m_shininess;
	bool m_clamping;
	
	std::string m_textureFile;
    int m_textureID;
	
	// contient le dernier matériau appliqué, pour éviter de rappeler
	// inutilement les fonctions glBindTexture/glMaterial qui sont couteuses
	static Material * lastApplied;
	
	// tableau des fichiers de texture à charger dans la carte graphique pour les charger
	// toutes en même temps de façon à éviter d'appeler glGenTextures plusieurs fois
    static std::vector<Material *> toLoad;
	
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
	
	void apply();
	
    static void loadTextures();
};

#endif