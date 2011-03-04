#include "MyScene.h"

#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100

MyScene::MyScene() : m_object("objects/android.txt"), m_light(GL_LIGHT0, Point(0, 3, 5), Vector(0, -.5, -1)), m_cameraPos(Point(0, 0, 5)), m_freeLook(false) {
}

// fonction appelée juste avant glutMainLoop
GLvoid MyScene::init() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	m_light.setDiffuse(1, 0, 0);
	m_light.setCutoff(10);
	m_light.setExponent(128);
}

// fonction de modélisation
GLvoid MyScene::display() {
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
	glRotated(glutGet(GLUT_ELAPSED_TIME)/2, 0, 1, 0);
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

GLvoid MyScene::keyPress(int key, int mouseX, int mouseY, bool specialKey) {
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

GLvoid MyScene::mousePress(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		// on peut regarder autour de nous en restant appuyé
		// sur le bouton gauche de la souris
		
		m_freeLook = (state == GLUT_DOWN);
	
		m_oldMouseX = x;
		m_oldMouseY = y;
	}
}

GLvoid MyScene::mouseMove(int x, int y) {
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