#ifndef ANGLE_H
#define ANGLE_H

class Angle {
private:
	double m_pitch;
	double m_yaw;
	double m_roll;

public:
	Angle(double pitch = 0, double yaw = 0, double roll = 0);
	
	double pitch();
	double yaw();
	double roll();
	
	void setPitch(double pitch);
	void setYaw(double yaw);
	void setRoll(double roll);	
	void addPitch(double pitch);
	void addYaw(double yaw);
	void addRoll(double roll);
};

#endif