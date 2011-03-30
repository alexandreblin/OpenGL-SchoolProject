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
	
	static void setGlobalAmbientLight(float r, float g, float b);
	static void setGlobalAmbientLight(float v);

protected:
	GLenum m_lightNum;
	Point m_position;
	Light::Type m_type;
	
	// permet de désactiver une lumière complètement, meme si enable() est appelé
	// (utilisé pour pouvoir éteindre/allumer la lumière avec une touche)
    bool m_isOn;

public:	
	Light(GLenum lightNum, Point position, Light::Type type = Light::POSITIONAL);
	
	virtual void place();
	
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setAmbient(float r, float g, float b);
	
	void setDiffuse(float v);
	void setSpecular(float v);
	void setAmbient(float v);
	
	Point & position();
	
	void enable();
	void disable();
	
    bool isOn();
    void setOn();
    void setOff();
};

#endif
