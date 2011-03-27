#include "Object.h"

using namespace std;

Object::Object(Point pos, Angle angle, Vector scale) : m_position(pos), m_angle(angle), m_scale(scale) {
}

Point & Object::position() {
	return m_position;
}

Angle & Object::angle() {
	return m_angle;
}