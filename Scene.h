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
#include "Point.h"
#include "Vector.h"
#include "Angle.h"
#include "Spot.h"

class Scene {
private:
	Mesh m_skybox;
	Mesh m_ground;
	MALP m_malp;
	
	Light m_light;
	
	enum CameraMode {
		FIRSTPERSON,
		FREELOOK
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
};

#endif