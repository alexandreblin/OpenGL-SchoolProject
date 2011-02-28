#include "Application.h"

Application* Application::appInstance = 0;

Application::Application(int *argc, char *argv[], std::string windowName) {
	Application::appInstance = this;
	
	glutInit(argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	
	glutCreateWindow(windowName.c_str());
	
	/*glutKeyboardFunc(&touche);
	glutSpecialFunc(&touche_speciale);
	
	glutMouseFunc(&boutonSouris);
	glutMotionFunc(&souris);*/
	
	glutDisplayFunc(this->displayCallback);
	glutIdleFunc(this->displayCallback);
	
	glutReshapeFunc(this->reshapeCallback);
		
	glClearColor(0, 0, 0, 0);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

GLvoid Application::reshapeCallback(GLsizei width, GLsizei height) {
	Application::instance()->reshape(width, height);
}

GLvoid Application::reshape(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(45, (GLdouble)width/(GLdouble)height, 1, 100);
	
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Application::displayCallback() {
	Application::instance()->display();
}

GLvoid Application::display() {
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

int Application::exec() {
	glutMainLoop();
	
	return 0;
}