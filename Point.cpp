#include "Point.h"

Point::Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {
}

Point::Point(const Point &p) : m_x(p.m_x), m_y(p.m_y), m_z(p.m_z) {
}

double Point::x() const {
	return m_x;
}

double Point::y() const {
	return m_y;
}

double Point::z() const {
	return m_z;
}

void Point::setX(double x) {
	m_x = x;
}

void Point::setY(double y) {
	m_y = y;
}

void Point::setZ(double z) {
	m_z = z;
}

void Point::addX(double offset) {
	m_x += offset;
}

void Point::addY(double offset) {
	m_y += offset;
}

void Point::addZ(double offset) {
	m_z += offset;
}

bool Point::operator==(const Point &other) const {
	return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

std::ostream & operator<<(std::ostream &out, const Point &p) {
	out << p.m_x << " " << p.m_y << " " << p.m_z;
	
	return out;
}