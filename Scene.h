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
	
	virtual	GLvoid keyPress(int key, int mouseX, int mouseY, bool specialKey = false) {}
	virtual GLvoid mousePress(int button, int state, int x, int y) {}
	virtual GLvoid mouseMove(int x, int y) {}
	virtual GLvoid init() = 0;
	virtual GLvoid display() = 0;
};

#endif