#ifndef ANGLE_H
#define ANGLE_H

#include <cmath>
#define PI 3.141592654589

#include "Vector.h"

class Angle {
private:
	float m_pitch;
	float m_yaw;
	float m_roll;

public:
	Angle(float pitch = 0, float yaw = 0, float roll = 0);
	
	Vector direction();
	
	float pitch();
	float yaw();
	float roll();
	
	void setPitch(float pitch);
	void setYaw(float yaw);
	void setRoll(float roll);	
	void addPitch(float pitch);
	void addYaw(float yaw);
	void addRoll(float roll);
	
	Angle & operator+=(const Angle &v);
	Angle & operator-=(const Angle &v);
	
	const Angle operator+(const Angle &v) const;
	const Angle operator-(const Angle &v) const;
};

#endif
