#include "MALP.h"

float MALP::MinArm1Pitch = 20;
float MALP::MaxArm1Pitch = 150;

float MALP::MinArm2Pitch = -90;
float MALP::MaxArm2Pitch = 0;

float MALP::MinArm2Yaw = -90;
float MALP::MaxArm2Yaw = 90;

float MALP::MinClawPitch = -30;
float MALP::MaxClawPitch = 0;

MALP::MALP(Point pos, Angle angle) : Object(pos, angle),
    // je ne donne pas de position à ces éléments car je les positionnerai à la main dans draw()
	m_body("objects/malp/body.obj"),
	m_arm1("objects/malp/arm1.obj", Point(), Angle(20, 0, 0)),
	m_arm2("objects/malp/arm2.obj"),
	m_clawTop("objects/malp/claw.obj"),
	m_clawBottom("objects/malp/claw.obj", Point(), Angle(0, 0, 180))
{
	m_wheels[0] = new Mesh("objects/malp/wheel.obj", Point(0.4393, 0.25614, 0.64042), Angle(0, 180, 0));
	m_wheels[1] = new Mesh("objects/malp/wheel.obj", Point(0.4393, 0.25614, 0.04112), Angle(0, 180, 0));
	m_wheels[2] = new Mesh("objects/malp/wheel.obj", Point(0.4393, 0.25614, -0.59398), Angle(0, 180, 0));
	m_wheels[3] = new Mesh("objects/malp/wheel.obj", Point(-0.4393, 0.25614, 0.64042));
	m_wheels[4] = new Mesh("objects/malp/wheel.obj", Point(-0.4393, 0.25614, 0.04112));
	m_wheels[5] = new Mesh("objects/malp/wheel.obj", Point(-0.4393, 0.25614, -0.59398));
}

MALP::~MALP() {
    for (int i = 0; i < 6; ++i)
        delete m_wheels[i];
}

void MALP::draw(bool keepMatrix) {
    if (!keepMatrix)
        glPushMatrix();
    
	glTranslatef(m_position.x(), m_position.y(), m_position.z());
	
	glRotatef(m_angle.pitch(), 1, 0, 0);
	glRotatef(m_angle.yaw(), 0, 1, 0);
	glRotatef(m_angle.roll(), 0, 0, 1);
	
	m_body.draw(true);
	
	glPushMatrix();
		glTranslatef(0, 0.80594, 0.70648);
		m_arm1.draw(true);
	
		glTranslatef(0, -0.02264, -0.58912);
		m_arm2.draw(true);
	
		glTranslatef(0, 0.45278, 0.70568);
		glRotatef(-25, 1, 0, 0);
	    
		m_clawTop.draw();
		m_clawBottom.draw();
	glPopMatrix();
	
	for (int i = 0; i < 6; ++i)
		m_wheels[i]->draw();
	
	if (!keepMatrix)
        glPopMatrix();
}

void MALP::moveForward(float dist) {
    for (int i = 0; i < 6; ++i) {
		m_wheels[i]->angle().addPitch(dist*400);
	}
	
    m_position += m_angle.direction() * dist;
    
    // on empêche le MALP de sortir de la scène
	if (m_position.x() > 14) m_position.setX(14);
	if (m_position.x() < -14) m_position.setX(-14);
    if (m_position.z() > 14) m_position.setZ(14);
    
    if (m_position.z() > -15) {
    	if (m_position.z() > 14) m_position.setZ(14);
    	if (m_position.z() < -14 && (m_position.y() > 3.3 || m_position.x() < -2 || m_position.x() > 2)) m_position.setZ(-14);
	}
	else {
    	if (m_position.z() < -44) m_position.setZ(-44);
    	if (m_position.z() > -16 && (m_position.y() > 3.3 || m_position.x() < -2 || m_position.x() > 2)) m_position.setZ(-16);
	}
}

void MALP::rotate(float angle) {
    for (int i = 0; i < 6; ++i) {
        if (i < 3)
		    m_wheels[i]->angle().addPitch(-angle*2);
		else
		    m_wheels[i]->angle().addPitch(angle*2);
	}
	
    m_angle.addYaw(angle);
}

void MALP::addArm1Pitch(float angle) {
    if (m_arm1.angle().pitch() - angle > MaxArm1Pitch) {
        m_arm1.angle().setPitch(MaxArm1Pitch);
    }
    else if (m_arm1.angle().pitch() - angle < MinArm1Pitch) {
        m_arm1.angle().setPitch(MinArm1Pitch);
    }
    else {
        m_arm1.angle().addPitch(-angle);
    }
}

void MALP::addArm2Pitch(float angle) {
    if (m_arm2.angle().pitch() + angle > MaxArm2Pitch) {
        m_arm2.angle().setPitch(MaxArm2Pitch);
    }
    else if (m_arm2.angle().pitch() + angle < MinArm2Pitch) {
        m_arm2.angle().setPitch(MinArm2Pitch);
    }
    else {
        m_arm2.angle().addPitch(angle);
    }
}

void MALP::addArm2Yaw(float angle) {
    if (m_arm2.angle().yaw() + angle > MaxArm2Yaw) {
        m_arm2.angle().setYaw(MaxArm2Yaw);
    }
    else if (m_arm2.angle().yaw() + angle < MinArm2Yaw) {
        m_arm2.angle().setYaw(MinArm2Yaw);
    }
    else {
        m_arm2.angle().addYaw(angle);
    }
}

void MALP::addClawPitch(float angle) {
    if (m_clawTop.angle().pitch() + angle > MaxClawPitch) {
        m_clawTop.angle().setPitch(MaxClawPitch);
        m_clawBottom.angle().setPitch(-MaxClawPitch);
    }
    else if (m_clawTop.angle().pitch() + angle < MinClawPitch) {
        m_clawTop.angle().setPitch(MinClawPitch);
        m_clawBottom.angle().setPitch(-MinClawPitch);
    }
    else {
        m_clawTop.angle().addPitch(angle);
        m_clawBottom.angle().addPitch(-angle);
    }
}