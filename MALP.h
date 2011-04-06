#ifndef MALP_H
#define MALP_H

#include "Object.h"
#include "Mesh.h"

class MALP : public Object {
private:
    static float MinArm1Pitch;
    static float MaxArm1Pitch;
    
    static float MinArm2Pitch;
    static float MaxArm2Pitch;
    
    static float MinArm2Yaw;
    static float MaxArm2Yaw;
    
    static float MinClawPitch;
    static float MaxClawPitch;
    
	Mesh m_body;
	Mesh m_arm1;
	Mesh m_arm2;
	Mesh m_clawTop;
	Mesh m_clawBottom;
	
	Mesh * m_wheels[6];
	
public:
	MALP(Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0));
    ~MALP();
	
	virtual void draw(bool keepMatrix = false);
	
    void moveForward(float dist);
    void rotate(float angle);
    
    void addArm1Pitch(float angle);
    void addArm2Pitch(float angle);
    void addArm2Yaw(float angle);
    void addClawPitch(float angle);
};

#endif
