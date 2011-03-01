#include "Point.h"

Point::Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {
}

Point::Point(const Point &p) : m_x(p.m_x), m_y(p.m_y), m_z(p.m_z) {
}

double Point::x() {
	return m_x;
}

double Point::y() {
	return m_y;
}

double Point::z() {
	return m_z;
}

bool Point::operator==(const Point &other) const {
	return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}

std::ostream & operator<<(std::ostream &out, const Point &p) {
	out << "(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
	
	return out;
}