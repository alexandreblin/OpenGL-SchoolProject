#include "Scene.h"
#include "Keyboard.h"

Point Scene::defaultCameraPos = Point(4, 4, 3);
Angle Scene::defaultCameraAngle = Angle(-20, 27, 0);

Scene::Scene() : 	m_skybox("objects/skybox.obj", Point(0, 0, 0), Angle(0, 180, 0)),
                    m_skybox2("objects/skybox_night.obj", Point(0, 0, -30)),
                    
					m_sand("objects/sand.obj"),
					m_pyramid("objects/pyramid.obj", Point(-5, 0, 5), Angle(0, 30, 0)),
					
					m_grass("objects/grass.obj", Point(0, 0, -30)),
                    m_temple("objects/temple.obj", Point(0, 0, -30)),
                    m_redsphere("objects/sphere.obj"),
                    m_bluesphere("objects/sphere.obj"),
                    m_greensphere("objects/sphere.obj"),
                    
					m_malp(Point(0, 0, -5), Angle(0, 180, 0)),
					m_malpClone(Point(8, 0, -5)),
					m_stargate(Point(0, 0, -15)),
					
					m_sunlight(GL_LIGHT0, Point(1, 1, -1), Light::DIRECTIONAL),
					m_moonlight(GL_LIGHT1, Point(0, 1, -1), Light::DIRECTIONAL),
					
					m_redlight(GL_LIGHT2, Point(0, 0, 0), Light::POSITIONAL),
					m_bluelight(GL_LIGHT3, Point(0, 0, 0), Light::POSITIONAL),
					m_greenlight(GL_LIGHT4, Point(0, 0, 0), Light::POSITIONAL),
					
					m_gatelight(GL_LIGHT5, Point(0, 1.5, -15), Light::POSITIONAL),
					
					m_cameraMode(FREELOOK),
					m_cameraPos(defaultCameraPos),
					m_cameraAngle(defaultCameraAngle)
{}

// fonction appelée juste avant glutMainLoop
GLvoid Scene::init() {
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
		
	glEnable(GL_TEXTURE_2D);
	
	Light::setGlobalAmbientLight(0.3);

	m_sunlight.setDiffuse(0.9);
	m_sunlight.setSpecular(0.9);
	
	m_moonlight.setDiffuse(0.2);
	m_moonlight.setSpecular(0.2);
	
    m_redlight.setDiffuse(1, 0, 0);
	
    m_redMaterial = new Material();
    m_redMaterial->setAmbient(0.4, 0, 0);
    m_redMaterial->setDiffuse(0.4, 0, 0);
    m_redMaterial->setEmission(0.5, 0, 0);
    m_redsphere.setMaterial(m_redMaterial);
	
    m_blueMaterial = new Material();
    m_blueMaterial->setAmbient(0, 0, 0.4);
    m_blueMaterial->setDiffuse(0, 0, 0.4);
    m_blueMaterial->setEmission(0, 0, 0.5);
    m_bluesphere.setMaterial(m_blueMaterial);
	
    m_bluelight.setDiffuse(0, 0, 1);
	
	m_greenMaterial = new Material();
    m_greenMaterial->setAmbient(0, 0.2, 0);
    m_greenMaterial->setDiffuse(0, 0.2, 0);
    m_greenMaterial->setEmission(0, 0.4, 0);
    m_greensphere.setMaterial(m_greenMaterial);
	
    m_greenlight.setDiffuse(0, .7, 0);
    
    m_gatelight.setDiffuse(0.16, 0.31, 0.9);
    m_gatelight.setAttenuation(1, 0, 0.05);
}

// fonction de modélisation
GLvoid Scene::display() {
	// Initialisation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	printFramerate();

	// Mise en place de la caméra
	if (m_cameraMode == FIRSTPERSON) {
		m_cameraAngle = Angle(0, m_malp.angle().yaw()+180, 0);
		m_cameraPos = m_malp.position() + Vector::normal(m_cameraAngle.direction(), Vector(0, 1, 0))*0.25 + Point(0, 1.2, 0);
	}
	
	glRotatef(-m_cameraAngle.pitch(), 1, 0, 0);
	glRotatef(-m_cameraAngle.yaw(), 0, 1, 0);
	glTranslatef(-m_cameraPos.x(), -m_cameraPos.y(), -m_cameraPos.z());
	
	// Affichage des skybox
	// on n'affiche que la skybox visible (sinon j'avais un petit bug d'affichage)
	if (m_cameraPos.z() > -15.1)
	    m_skybox.draw();
	
	if (m_cameraPos.z() < -14.9)
	    m_skybox2.draw();
	

	// Mise en place de la lumière du désert
    m_sunlight.place();
    m_sunlight.enable();
    
    // on dessine le malp et la porte avec l'éclairage du désert
    // seulement si la caméra est présente dans le désert également
	if (m_cameraPos.z() > -15) {
		m_malp.draw();
		m_stargate.draw();
    }

	
	// Dessin des objets
	m_sand.draw();
    m_pyramid.draw();

    drawReplique();
  	
  	m_sunlight.disable();
  	
    m_moonlight.place();
    m_moonlight.enable();
    
    m_gatelight.place();
    m_gatelight.enable();
    
    glPushMatrix();
        glTranslatef(-2, 2+cos(glutGet(GLUT_ELAPSED_TIME)/1000.0), -30);
        glRotatef(-180+glutGet(GLUT_ELAPSED_TIME)/10.0, 0, 1, 0);
        glTranslatef(0, 0, -1.5);
        m_redlight.place();
        m_redlight.enable();
        m_redsphere.draw();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(2, 2+sin(glutGet(GLUT_ELAPSED_TIME)/1000.0), -30);
        glRotatef(-180+glutGet(GLUT_ELAPSED_TIME)/10.0, 0, 1, 0);
        glTranslatef(0, 0, 1.5);
        m_bluelight.place();
        m_bluelight.enable();
        m_bluesphere.draw();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 2+sin(glutGet(GLUT_ELAPSED_TIME)/500.0), -30+sin(glutGet(GLUT_ELAPSED_TIME)/1000.0)*2);
        m_greenlight.place();
        m_greenlight.enable();
        m_greensphere.draw();
    glPopMatrix();
  	
  	m_grass.draw();
  	
    m_temple.draw();
  	
  	if (m_cameraPos.z() < -15) {
    	m_malp.draw();
      	m_stargate.draw();
    }
  	
    m_moonlight.disable();
    m_redlight.disable();
    m_bluelight.disable();
    m_greenlight.disable();
  	
	glutSwapBuffers();
}

void Scene::drawReplique() {
    static int nextMove = glutGet(GLUT_ELAPSED_TIME);
    static int nextDirectionChange = nextMove + 4000;
    if (glutGet(GLUT_ELAPSED_TIME) >= nextMove) {
        static int sens = 1;
        
        if (glutGet(GLUT_ELAPSED_TIME) > nextDirectionChange) {
            sens = -sens;
            nextDirectionChange = glutGet(GLUT_ELAPSED_TIME) + 4000;
        }
        m_malpClone.rotate(-0.5);
        m_malpClone.moveForward(0.01);
        m_malpClone.addArm1Pitch(-0.3*sens);
        m_malpClone.addArm2Pitch(0.2*sens);
        m_malpClone.addArm2Yaw(0.6*sens);
        m_malpClone.addClawPitch(1*sens);
        
        nextMove = glutGet(GLUT_ELAPSED_TIME) + 10;
    }
    
    m_malpClone.draw();
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
			m_cameraPos -= dir * 0.2;
			break;
		case KEY_Q:
			m_cameraPos += perp * 0.2;
			break;
		case KEY_S:
			m_cameraPos += dir * 0.2;
			break;
		case KEY_D:
			m_cameraPos -= perp * 0.2;
			break;
		case KEY_C:
			m_cameraMode = (m_cameraMode == FREELOOK ? FIRSTPERSON : FREELOOK);
			break;
        case KEY_R:
            m_malp.addArm1Pitch(-1);
            break;
        case KEY_MAJ+KEY_R:
            m_malp.addArm1Pitch(1);
            break;
        case KEY_T:
            m_malp.addArm2Pitch(-1);
            break;
        case KEY_MAJ+KEY_T:
            m_malp.addArm2Pitch(1);
            break;
        case KEY_Y:
            m_malp.addArm2Yaw(-1);
            break;
        case KEY_MAJ+KEY_Y:
            m_malp.addArm2Yaw(1);
            break;
        case KEY_U:
            m_malp.addClawPitch(-1);
            break;
        case KEY_MAJ+KEY_U:
            m_malp.addClawPitch(1);
            break;
        case KEY_L:
            if (m_redlight.isOn()) {
                m_redlight.setOff();
                m_bluelight.setOff();
                m_greenlight.setOff();
                
                m_redMaterial->setEmission(0, 0, 0);
                m_blueMaterial->setEmission(0, 0, 0);
                m_greenMaterial->setEmission(0, 0, 0);
            }
            else {
                m_redlight.setOn();
                m_bluelight.setOn();
                m_greenlight.setOn();
                
                m_redMaterial->setEmission(0.5, 0, 0);
                m_blueMaterial->setEmission(0, 0, 0.5);
                m_greenMaterial->setEmission(0, 0.4, 0);
            }
            break;
        case KEY_SPACE:
            m_cameraPos = defaultCameraPos;
            m_cameraAngle = defaultCameraAngle;
            m_cameraMode = FREELOOK;
            break;
		}
	}
	else {
	    switch (key) {
        case GLUT_KEY_UP:
            m_malp.moveForward(0.03);
            break;
        case GLUT_KEY_DOWN:
            m_malp.moveForward(-0.03);
            break;
        case GLUT_KEY_LEFT:
            m_malp.rotate(1);
            break;
        case GLUT_KEY_RIGHT:
            m_malp.rotate(-1);
            break;
	    }
	}
	
	if (m_cameraPos.x() > 14.8) m_cameraPos.setX(14.8);
	if (m_cameraPos.x() < -14.8) m_cameraPos.setX(-14.8);
	if (m_cameraPos.y() > 14.8) m_cameraPos.setY(14.8);
	if (m_cameraPos.y() < 0.2) m_cameraPos.setY(0.2);
	
	if (m_cameraPos.z() > -15) {
    	if (m_cameraPos.z() > 14.8) m_cameraPos.setZ(14.8);
    	if (m_cameraPos.z() < -14.8 && (m_cameraPos.y() > 3.3 || m_cameraPos.x() < -2 || m_cameraPos.x() > 2)) m_cameraPos.setZ(-14.8);
	}
	else {
    	if (m_cameraPos.z() < -44.8) m_cameraPos.setZ(-44.8);
    	if (m_cameraPos.z() > -15.2 && (m_cameraPos.y() > 3.3 || m_cameraPos.x() < -2 || m_cameraPos.x() > 2)) m_cameraPos.setZ(-15.2);
	}
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
	
	int deltaX = x - m_oldMouseX;
	int deltaY = y - m_oldMouseY;
	
	// on fait tourner la caméra proportionellement aux dimensions de la
	// fenêtre pour que le mouvement soit uniforme quelle que soit sa taille

	m_cameraAngle.addYaw(-deltaX/(float)glutGet(GLUT_WINDOW_WIDTH) * 180);
	m_cameraAngle.addPitch(-deltaY/(float)glutGet(GLUT_WINDOW_HEIGHT) * 180);
		
	m_oldMouseX = x;
	m_oldMouseY = y;
}