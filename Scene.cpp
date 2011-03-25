#include "Scene.h"

#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100

Scene::Scene() : m_object("objects/malp.obj", Point(0, -0.2, 3.5), Angle(0, 0, 0), Vector(0.01, 0.01, 0.01)), m_light(GL_LIGHT0, Point(-2, 2, 2), Light::POSITIONAL), m_cameraPos(Point(0, 0, 5)), m_freeLook(false) {
}

// fonction appelée juste avant glutMainLoop
GLvoid Scene::init() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
		
	glEnable(GL_TEXTURE_2D);
	
	GLfloat lumiere_ambiente[] = {0.5f, 0.5f, 0.5f, 0.0f};
   	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lumiere_ambiente);
	
	m_light.setDiffuse(0.7, 0.7, 0.7);
	m_light.setAmbient(0, 0, 0);
	m_light.setSpecular(0.9, 0.9, 0.9);
}

// fonction de modélisation
GLvoid Scene::display() {
	// Initialisation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	// Mise en place de la caméra
	if (m_cameraAngle.pitch() != 0)
		glRotated(-m_cameraAngle.pitch(), 1, 0, 0);
		
	if (m_cameraAngle.yaw() != 0)
		glRotated(-m_cameraAngle.yaw(), 0, 1, 0);

	glTranslated(-m_cameraPos.x(), -m_cameraPos.y(), -m_cameraPos.z());


	// Mise en place de la lumière
	glPushMatrix();
		m_light.place();
		m_light.enable();
	glPopMatrix();
	
	
	// Dessin des objets
	glPushMatrix();
	{
		m_object.draw();
  	}
  	glPopMatrix();
	
	
	glutSwapBuffers();
}

GLvoid Scene::reshape(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(45, (GLdouble)width/(GLdouble)height, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
}

GLvoid Scene::keyPress(int key, int mouseX, int mouseY, bool specialKey) {
	// vecteur correspondant à la direction de la caméra
	Vector dir = m_cameraAngle.direction();
	
	// vecteur "perpendiculaire" à la direction pour se déplacer latéralement
	Vector perp = Vector::normal(dir, Vector(0, 1, 0));
	
	if (!specialKey) {
		switch (key) {
		case KEY_Z:
			m_cameraPos += dir * 0.2;
			break;
		case KEY_Q:
			m_cameraPos -= perp * 0.2;
			break;
		case KEY_S:
			m_cameraPos -= dir * 0.2;
			break;
		case KEY_D:
			m_cameraPos += perp * 0.2;
			break;
		}
	}
}

GLvoid Scene::mousePress(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		// on peut regarder autour de nous en restant appuyé
		// sur le bouton gauche de la souris
		
		m_freeLook = (state == GLUT_DOWN);
	
		m_oldMouseX = x;
		m_oldMouseY = y;
	}
}

GLvoid Scene::mouseMove(int x, int y) {
	if (m_freeLook) {
		int deltaX = m_oldMouseX - x;
		int deltaY = m_oldMouseY - y;
		
		// on fait tourner la caméra proportionellement aux dimensions de la
		// fenêtre pour que le mouvement soit uniforme quelle que soit sa taille

		m_cameraAngle.addYaw(deltaX/(double)glutGet(GLUT_WINDOW_WIDTH) * 180);
		m_cameraAngle.addPitch(deltaY/(double)glutGet(GLUT_WINDOW_HEIGHT) * 180);
		
		m_oldMouseX = x;
		m_oldMouseY = y;
	}
}