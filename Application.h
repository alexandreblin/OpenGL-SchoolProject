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
	Application();
	
	static Application *appInstance;
	Scene *m_scene;
	
public:
    ~Application();
    
    // Application ne peut être instanciée qu'une seule fois par exécution
	static Application* instance() {
		if (!appInstance)
			appInstance = new Application();

		return appInstance;
	}
	
	void setup(int *argc, char *argv[], std::string windowName);
	
	Scene * scene();
	
	static GLvoid reshapeCallback(GLsizei width, GLsizei height);
	static GLvoid displayCallback();
	static GLvoid keyboardCallback(unsigned char key, int x, int y);
	static GLvoid specialKeyCallback(int key, int x, int y);
	static GLvoid mousePressCallback(int button, int state, int x, int y);
	static GLvoid mouseMoveCallback(int x, int y);
	static void exitCallback();
	
	int exec();
	
	// on déclare les constructeurs par recopie et l'opérateur d'assignation
	// sans les implémenter pour ne pas que l'objet puisse être copié
	Application(const Application &a);
	void operator=(const Application &a);
};

#endif