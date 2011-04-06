#include "Object.h"

using namespace std;

Object::Object(Point pos, Angle angle) : m_position(pos), m_angle(angle) {
}

Point & Object::position() {
	return m_position;
}

Angle & Object::angle() {
	return m_angle;
}
