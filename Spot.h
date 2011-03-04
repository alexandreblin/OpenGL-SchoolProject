#ifndef SPOT_H
#define SPOT_H

#include "Light.h"
#include "Vector.h"

class Spot : public Light {
private:
	Vector m_direction;

public:
	Spot(GLenum lightNum, Point position, Vector direction);
	
	void place();
	
	void setCutoff(float cutoff);
	void setExponent(float exponent);
	
	Vector & direction();
};

#endif