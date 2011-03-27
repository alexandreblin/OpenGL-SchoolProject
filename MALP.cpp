#include "MALP.h"

MALP::MALP(Point pos, Angle angle, Vector scale) : Object(pos, angle, scale),
	m_body("objects/malp/body.obj", m_position, m_angle, m_scale),
	m_arm1("objects/malp/arm1.obj", Point(), Angle(-20, 0, 0)),
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

void MALP::draw() {
	m_body.draw();
	
	glPushMatrix();
		glTranslatef(0, 0.80594, 0.70648);
		m_arm1.draw();
	
		glTranslatef(0, -0.02264, -0.58912);
		m_arm2.draw();
	
		glTranslatef(0, 0.45278, 0.70568);
		glRotatef(-25, 1, 0, 0);
	
		glPushMatrix();
			m_clawTop.draw();
		glPopMatrix();
	
		glPushMatrix();
			m_clawBottom.draw();
		glPopMatrix();
	glPopMatrix();
	
	for (int i = 0; i < 6; ++i) {
		glPushMatrix();
		m_wheels[i]->draw();
		glPopMatrix();
	}
}