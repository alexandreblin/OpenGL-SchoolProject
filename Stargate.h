#ifndef STARGATE_H
#define STARGATE_H

#include "Object.h"
#include "Mesh.h"
#include "Material.h"

class Stargate : public Object {
private:
    Mesh m_gate;
	Mesh m_horizonFront;
	Mesh m_horizonBack;
	
	// l'animation
    Material * m_horizonMaterials[31];
	
public:
	Stargate(Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0));
	
	virtual void draw(bool keepMatrix = false);
};

#endif