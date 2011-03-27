#ifndef MALP_H
#define MALP_H

#include "Object.h"
#include "Mesh.h"

class MALP : public Object {
private:
	Mesh m_body;
	Mesh m_arm1;
	Mesh m_arm2;
	Mesh m_clawTop;
	Mesh m_clawBottom;
	
	Mesh * m_wheels[6];
	
public:
	MALP(Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0), Vector scale = Vector(1, 1, 1));
	
	virtual void draw();
};

#endif