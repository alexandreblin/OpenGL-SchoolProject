#include "Vector.h"

Vector::Vector(double x, double y, double z) : Point(x, y, z) {
}

Vector::Vector(Point a, Point b) : Point(b.x() - a.x(), b.y() - a.y(), b.z() - a.z()) {
}

Vector::Vector(const Vector &v) : Point(v) {
}


double Vector::length() {
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

Vector Vector::normalized() {
	double l = length();
	
	return Vector(m_x/l, m_y/l, m_z/l);
}

Vector Vector::normal(Vector a, Vector b) {
	return Vector(a.y()*b.z() - a.z()*b.y(),
				  a.z()*b.x() - a.x()*b.z(),
				  a.x()*b.y() - a.y()*b.x()).normalized();
}


Vector & Vector::operator+=(const Vector &v) {
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	
	return *this;
}

Vector & Vector::operator-=(const Vector &v) {
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	
	return *this;
}

Vector & Vector::operator*=(double scalar) {
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
	
	return *this;
}

const Vector Vector::operator+(const Vector &v) const {
	Vector res = *this;
	
	res += v;
	
	return res;
}

const Vector Vector::operator-(const Vector &v) const {
	Vector res = *this;
	
	res -= v;
	
	return res;
}

const Vector Vector::operator*(double scalar) const {
	Vector res = *this;
	
	res *= scalar;
	
	return res;
}

/*
 * Opérateurs surchargés pour ajouter un vecteur à un point
 */
Point & operator+=(Point &p, const Vector &v) {
	p.addX(v.m_x);
	p.addY(v.m_y);
	p.addZ(v.m_z);
	
	return p;
}

Point & operator-=(Point &p, const Vector &v) {
	p.addX(-v.m_x);
	p.addY(-v.m_y);
	p.addZ(-v.m_z);
	
	return p;
}

const Point operator+(const Point &p, const Vector &v) {
	Point res = p;
	
	res += v;
	
	return res;
}

const Point operator-(const Point &p, const Vector &v) {
	Point res = p;
	
	res -= v;
	
	return res;
}