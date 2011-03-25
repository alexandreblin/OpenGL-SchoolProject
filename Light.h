#ifndef LIGHT_H
#define LIGHT_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Point.h"

class Light {
public:
	enum Type {
		DIRECTIONAL = 0,
		POSITIONAL = 1
	};

protected:
	GLenum m_lightNum;
	Point m_position;
	Light::Type m_type;

public:	
	Light(GLenum lightNum, Point position, Light::Type type = Light::POSITIONAL);
	
	virtual void place();
	
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setAmbient(float r, float g, float b);
	
	Point & position();
	
	void enable();
	void disable();
};

#endif
