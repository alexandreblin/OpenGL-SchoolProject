#ifndef SCENE_H
#define SCENE_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Mesh.h"
#include "MALP.h"
#include "Stargate.h"
#include "Point.h"
#include "Vector.h"
#include "Angle.h"
#include "Light.h"
#include "Stargate.h"

class Scene {
private:
	Mesh m_skybox;
	Mesh m_skybox2;
	
	Mesh m_sand;
	Mesh m_pyramid;
	
	Mesh m_grass;
	Mesh m_temple;
	
    Mesh m_redsphere;
    Mesh m_bluesphere;
    Mesh m_greensphere;
    
    Material * m_redMaterial;
    Material * m_blueMaterial;
    Material * m_greenMaterial;
    
	MALP m_malp;
	MALP m_malpClone;
	Stargate m_stargate;
	
	Light m_sunlight;
	Light m_moonlight;
	
	Light m_redlight;
	Light m_bluelight;
	Light m_greenlight;
	
    Light m_gatelight;
	
	enum CameraMode {
		FIRSTPERSON, // première personne
		FREELOOK // caméra libre
	};
	
	CameraMode m_cameraMode;
	Point m_cameraPos;
	Angle m_cameraAngle;
	
    static Point defaultCameraPos;
    static Angle defaultCameraAngle;
	
	// variables permettant de calculer le déplacement relatif de la souris
	int m_oldMouseX;
	int m_oldMouseY;
	
public:
	Scene();
	
	GLvoid init();
	GLvoid display();
	GLvoid reshape(GLsizei width, GLsizei height);
	GLvoid keyPress(int key, int mouseX, int mouseY, bool specialKey = false);
	GLvoid mousePress(int button, int state, int x, int y);
	GLvoid mouseMove(int x, int y);

private:
	void printFramerate();
	
    void drawReplique();
};

#endif
