#ifndef SCENE_H
#define SCENE_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class Scene {
private:
	
public:
	Scene();
	
	GLvoid reshape(GLsizei width, GLsizei height);
	virtual GLvoid display() = 0;
};

#endif