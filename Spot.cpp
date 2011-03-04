#include "Spot.h"

Spot::Spot(GLenum lightNum, Point position, Vector direction) : Light(lightNum, position, Light::POSITIONAL), m_direction(direction) {
}

void Spot::place() {
	GLfloat direction[] = {m_direction.x(), m_direction.y(), m_direction.z()};
	glLightfv(m_lightNum, GL_SPOT_DIRECTION, direction);
	
	Light::place();
}

void Spot::setCutoff(float cutoff) {
	glLightf(m_lightNum, GL_SPOT_CUTOFF, cutoff);
}

void Spot::setExponent(float exponent) {
	glLightf(m_lightNum, GL_SPOT_EXPONENT, exponent);
}

Vector & Spot::direction() {
	return m_direction;
}