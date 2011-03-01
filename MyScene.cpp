#include "MyScene.h"

MyScene::MyScene() {
}

GLvoid MyScene::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	glTranslatef(0, 0, -5);
	
	glPushMatrix();
	{
    	glutSolidCube(0.5);
  	}
  	glPopMatrix();
	
	glutSwapBuffers();
}