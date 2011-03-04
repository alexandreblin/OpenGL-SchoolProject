#ifndef MYSCENE_H
#define MYSCENE_H

#include "Scene.h"
#include "Object.h"
#include "Point.h"
#include "Vector.h"
#include "Angle.h"
#include "Spot.h"

class MyScene : public Scene {
private:
	Object m_object;
	Spot m_light;
	
	Point m_cameraPos;
	Angle m_cameraAngle;
	
	bool m_freeLook;
	// variables permettant de calculer le déplacement relatif de la souris
	int m_oldMouseX;
	int m_oldMouseY;
	
public:
	MyScene();
	
	GLvoid init();
	GLvoid display();
	GLvoid keyPress(int key, int mouseX, int mouseY, bool specialKey = false);
	GLvoid mousePress(int button, int state, int x, int y);
	GLvoid mouseMove(int x, int y);
};

#endif