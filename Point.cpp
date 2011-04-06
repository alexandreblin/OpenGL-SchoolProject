#include "Point.h"

Point::Point(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {
}

Point::Point(const Point &p) : m_x(p.m_x), m_y(p.m_y), m_z(p.m_z) {
}

float Point::x() const {
	return m_x;
}

float Point::y() const {
	return m_y;
}

float Point::z() const {
	return m_z;
}

void Point::setX(float x) {
	m_x = x;
}

void Point::setY(float y) {
	m_y = y;
}

void Point::setZ(float z) {
	m_z = z;
}

void Point::addX(float offset) {
	m_x += offset;
}

void Point::addY(float offset) {
	m_y += offset;
}

void Point::addZ(float offset) {
	m_z += offset;
}

bool Point::operator==(const Point &other) const {
	return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

Point & Point::operator+=(const Point &p) {
	m_x += p.m_x;
	m_y += p.m_y;
	m_z += p.m_z;
	
	return *this;
}

Point & Point::operator-=(const Point &p) {
	m_x -= p.m_x;
	m_y -= p.m_y;
	m_z -= p.m_z;
	
	return *this;
}

const Point Point::operator+(const Point &p) const {
	Point res = *this;
	
	res += p;
	
	return res;
}

const Point Point::operator-(const Point &p) const {
	Point res = *this;
	
	res -= p;
	
	return res;
}

std::ostream & operator<<(std::ostream &out, const Point &p) {
	out << p.m_x << " " << p.m_y << " " << p.m_z;
	
	return out;
}
