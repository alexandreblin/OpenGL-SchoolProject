#include "Scene.h"

Scene::Scene() {
}

GLvoid Scene::reshape(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(45, (GLdouble)width/(GLdouble)height, 1, 100);
	
	glMatrixMode(GL_MODELVIEW);
}