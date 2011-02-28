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

class Application {
private:
	static Application *appInstance;
	
public:
	Application(int *argc, char *argv[], std::string windowName);
	
	static Application* instance() {
		return appInstance;
	}
	
	static GLvoid reshapeCallback(GLsizei width, GLsizei height);
	GLvoid reshape(GLsizei width, GLsizei height);
	
	static GLvoid displayCallback();
	GLvoid display();
	
	int exec();
};

#endif