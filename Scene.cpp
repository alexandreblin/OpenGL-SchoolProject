#include "Scene.h"

#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100
#define KEY_C 99

Scene::Scene() : 	m_skybox("objects/skybox.obj"),
					m_ground("objects/ground.obj"),
					m_malp("objects/malp.obj", Point(0, 0, 0), Angle(0, 90, 0)),
					
					m_light(GL_LIGHT0, Point(-1, 1, 1), Light::DIRECTIONAL),
					
					m_cameraMode(FREELOOK),
					m_cameraPos(Point(0, 1, 4))
{}

// fonction appelée juste avant glutMainLoop
GLvoid Scene::init() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
		
	glEnable(GL_TEXTURE_2D);
	
	Light::setGlobalAmbientLight(0.1);
	
	m_light.setDiffuse(0.9);
	m_light.setAmbient(0);
	m_light.setSpecular(1);
}

// fonction de modélisation
GLvoid Scene::display() {
	// Initialisation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	printFramerate();

	// Mise en place de la caméra
	if (m_cameraMode == FIRSTPERSON) {
		m_cameraAngle = Angle(0, -m_malp.angle().yaw() + 180, 0);
		m_cameraPos = m_malp.position() + Vector::normal(m_cameraAngle.direction(), Vector(0, 1, 0))*-0.25 + Point(0, 1.2, 0);
	}
	
	if (m_cameraAngle.pitch() != 0)
		glRotatef(-m_cameraAngle.pitch(), 1, 0, 0);
		
	if (m_cameraAngle.yaw() != 0)
		glRotatef(-m_cameraAngle.yaw(), 0, 1, 0);

	glTranslatef(-m_cameraPos.x(), -m_cameraPos.y(), -m_cameraPos.z());


	// Mise en place de la lumière
	glPushMatrix();
		m_light.place();
		m_light.enable();
	glPopMatrix();
	
	
	// Affichage de la skybox
	glPushMatrix();
		// on désactive l'éclairage, la skybox est toujours illuminée
		glDisable(GL_LIGHTING);
		m_skybox.draw();
		glEnable(GL_LIGHTING);
  	glPopMatrix();
	
	
	// Dessin des objets
	glPushMatrix();
		m_ground.draw();
  	glPopMatrix();
	
	glPushMatrix();
		m_malp.draw();
  	glPopMatrix();

	
	glutSwapBuffers();
}

void Scene::printFramerate() {
	static int nextTime = glutGet(GLUT_ELAPSED_TIME) + 1000;
	static int nbFrame = 0;
	
	if (glutGet(GLUT_ELAPSED_TIME) >= nextTime) {
		std::cout << "FPS: " << nbFrame << std::endl;
		nbFrame = 0;
		nextTime = glutGet(GLUT_ELAPSED_TIME) + 1000;
	}
	
	nbFrame++;
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
		case KEY_C:
			m_cameraMode = (m_cameraMode == FREELOOK ? FIRSTPERSON : FREELOOK);
			break;
		}
	}
	
	if (m_cameraPos.x() > 29.5) m_cameraPos.setX(29.5);
	if (m_cameraPos.x() < -29.5) m_cameraPos.setX(-29.5);
	if (m_cameraPos.y() > 29.5) m_cameraPos.setY(29.5);
	if (m_cameraPos.y() < -29.5) m_cameraPos.setY(-29.5);
	if (m_cameraPos.z() > 29.5) m_cameraPos.setZ(29.5);
	if (m_cameraPos.z() < -29.5) m_cameraPos.setZ(-29.5);
}

GLvoid Scene::mousePress(int button, int state, int x, int y) {
	if (m_cameraMode != FREELOOK)
		return;
	
	// on initialise les variables qui permettrons de savoir
	// de combien la souris s'est déplacée pour bouger la caméra
	m_oldMouseX = x;
	m_oldMouseY = y;
}

GLvoid Scene::mouseMove(int x, int y) {
	if (m_cameraMode != FREELOOK)
		return;
	
	int deltaX = m_oldMouseX - x;
	int deltaY = m_oldMouseY - y;
	
	// on fait tourner la caméra proportionellement aux dimensions de la
	// fenêtre pour que le mouvement soit uniforme quelle que soit sa taille

	m_cameraAngle.addYaw(deltaX/(float)glutGet(GLUT_WINDOW_WIDTH) * 180);
	m_cameraAngle.addPitch(deltaY/(float)glutGet(GLUT_WINDOW_HEIGHT) * 180);
	
	m_oldMouseX = x;
	m_oldMouseY = y;
}