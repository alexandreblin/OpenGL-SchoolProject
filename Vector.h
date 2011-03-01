#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "Point.h"

class Vector : public Point {
private:
	
public:
	Vector(double x, double y, double z);
	Vector(Point a, Point b);
	Vector(const Vector &v);
	
	Vector & operator+=(const Vector &v);
	Vector & operator-=(const Vector &v);
	Vector & operator*=(double scalar);
	
	const Vector operator+(const Vector &v) const;
	const Vector operator-(const Vector &v) const;
	const Vector operator*(double scalar) const;
	
	double length();
	Vector normalized();
	
	static Vector normal(Vector a, Vector b);
};

#endif