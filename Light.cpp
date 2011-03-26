#include "Light.h"

void Light::setGlobalAmbientLight(float r, float g, float b) {
	GLfloat ambient[4] = {r, g, b, 0};
   	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

Light::Light(GLenum lightNum, Point position, Light::Type type) : m_lightNum(lightNum), m_position(position), m_type(type) {
}

void Light::place() {
	GLfloat position[] = {m_position.x(), m_position.y(), m_position.z(), m_type};
	glLightfv(m_lightNum, GL_POSITION, position);
}

void Light::setDiffuse(float r, float g, float b) {
	float diffuse[4] = {r, g, b, 1};
	glLightfv(m_lightNum, GL_DIFFUSE, diffuse);
}

void Light::setSpecular(float r, float g, float b) {
	float specular[4] = {r, g, b, 1};
	glLightfv(m_lightNum, GL_SPECULAR, specular);
}

void Light::setAmbient(float r, float g, float b) {
	float ambient[4] = {r, g, b, 1};
	glLightfv(m_lightNum, GL_AMBIENT, ambient);
}

void Light::enable() {
	glEnable(m_lightNum);
}

void Light::disable() {
	glDisable(m_lightNum);
}

Point & Light::position() {
	return m_position;
}
