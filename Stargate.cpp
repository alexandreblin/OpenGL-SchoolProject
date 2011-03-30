#include "Stargate.h"

using namespace std;

Stargate::Stargate(Point pos, Angle angle, Vector scale) : Object(pos, angle, scale),
    m_gate("objects/stargate/stargate.obj"),
	m_horizonFront("objects/stargate/horizon.obj", Point(0, 0, 0.17)),
	m_horizonBack("objects/stargate/horizon.obj", Point(0, 0, -0.17), Angle(0, 180, 0))
{
    for (int i = 0; i < 31; ++i) {
        Material *m = new Material();
        
        char num[3];
        sprintf(num, "%02d", i+1);
        
        m->setEmission(1, 1, 1); // l'horizon des évènements "émet" de la lumière
        m->setTextureFile("objects/textures/horizon/puddle_" + string(num) + ".png");
        
        m_horizonMaterials[i] = m;
    }
}

void Stargate::draw(bool keepMatrix) {
    if (!keepMatrix)
        glPushMatrix();
    
	glTranslatef(m_position.x(), m_position.y() + 1.5, m_position.z());
	
	glRotatef(m_angle.pitch(), 1, 0, 0);
	glRotatef(m_angle.yaw(), 0, 1, 0);
	glRotatef(m_angle.roll(), 0, 0, 1);
	    
    // on applique l'animation
    m_horizonFront.setMaterial(m_horizonMaterials[(glutGet(GLUT_ELAPSED_TIME)/40)%30]);
    m_horizonBack.setMaterial(m_horizonMaterials[(glutGet(GLUT_ELAPSED_TIME)/40)%30]);
    
    // on le dessine de chaque coté
	m_horizonFront.draw();
	m_horizonBack.draw();
	
    m_gate.draw();
    
    if (!keepMatrix)
        glPopMatrix();
}