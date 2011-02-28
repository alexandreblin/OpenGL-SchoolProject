#include "Application.h"

Application* Application::appInstance = 0;

Application::Application() : m_scene(NULL) {
}

void Application::setup(int *argc, char *argv[], std::string windowName, Scene *scene) {	
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
	
	m_scene = scene;
}

Scene* Application::scene() {
	return m_scene;
}

GLvoid Application::reshapeCallback(GLsizei width, GLsizei height) {
	Application::instance()->scene()->reshape(width, height);
}

GLvoid Application::displayCallback() {
	Application::instance()->scene()->display();
}

int Application::exec() {
	glutMainLoop();
	
	return 0;
}