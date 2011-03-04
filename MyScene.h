#ifndef MYSCENE_H
#define MYSCENE_H

#include <cmath>
#define PI 3.141592654589

#include "Scene.h"
#include "Object.h"
#include "Point.h"
#include "Vector.h"
#include "Angle.h"

class MyScene : public Scene {
private:
	Object m_object;
	
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