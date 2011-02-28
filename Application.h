#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>
#include "Scene.h"

class Application {
private:
	static Application *appInstance;
	Scene m_scene;
	
public:
	Application(int *argc, char *argv[], std::string windowName);
	
	static Application* instance() {
		return appInstance;
	}
	
	Scene scene();
	
	static GLvoid reshapeCallback(GLsizei width, GLsizei height);
	static GLvoid displayCallback();
	
	int exec();
};

#endif