#include "Application.h"

Application* Application::appInstance = 0;

Application::Application() : m_scene() {
}

void Application::setup(int *argc, char *argv[], std::string windowName) {	
	glutInit(argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	
	glutCreateWindow(windowName.c_str());
	
	glutKeyboardFunc(this->keyboardCallback);
	glutSpecialFunc(this->specialKeyCallback);
	
	glutMouseFunc(this->mousePressCallback);
	glutMotionFunc(this->mouseMoveCallback);
	
	glutDisplayFunc(this->displayCallback);
	glutIdleFunc(this->displayCallback);
	
	glutReshapeFunc(this->reshapeCallback);
		
	glClearColor(0, 0, 0, 0);
		
	m_scene.init();
}

Scene & Application::scene() {
	return m_scene;
}

GLvoid Application::reshapeCallback(GLsizei width, GLsizei height) {
	Application::instance()->scene().reshape(width, height);
}

GLvoid Application::displayCallback() {
	Application::instance()->scene().display();
}

GLvoid Application::keyboardCallback(unsigned char key, int x, int y) {
	Application::instance()->scene().keyPress(key, x, y);
}

GLvoid Application::specialKeyCallback(int key, int x, int y) {
	Application::instance()->scene().keyPress(key, x, y, true);
}

GLvoid Application::mousePressCallback(int button, int state, int x, int y) {
	Application::instance()->scene().mousePress(button, state, x, y);
}

GLvoid Application::mouseMoveCallback(int x, int y) {
	Application::instance()->scene().mouseMove(x, y);
}


int Application::exec() {
	glutMainLoop();
	
	return 0;
}