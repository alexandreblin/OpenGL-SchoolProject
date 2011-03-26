#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "Point.h"

class Vector : public Point {
private:
	
public:
	Vector(float x = 0, float y = 0, float z = 0);
	Vector(Point a, Point b);
	Vector(const Vector &v);
	
	float length();
	Vector normalized();
	
	static Vector normal(Vector a, Vector b);
	
	Vector & operator+=(const Vector &v);
	Vector & operator-=(const Vector &v);
	Vector & operator*=(float scalar);
	
	const Vector operator+(const Vector &v) const;
	const Vector operator-(const Vector &v) const;
	const Vector operator*(float scalar) const;
	
	friend Point & operator+=(Point &p, const Vector &v);
	friend Point & operator-=(Point &p, const Vector &v);
	friend const Point operator+(const Point &p, const Vector &v);
	friend const Point operator-(const Point &p, const Vector &v);
};

#endif