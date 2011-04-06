#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
protected:
	float m_x;
	float m_y;
	float m_z;
	
public:
	Point(float x = 0, float y = 0, float z = 0);
	Point(const Point &p);
	
	float x() const;
	float y() const;
	float z() const;
	
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	void addX(float offset);
	void addY(float offset);
	void addZ(float offset);
	
	bool operator==(const Point &other) const;
	
	Point & operator+=(const Point &p);
	Point & operator-=(const Point &p);
	
	const Point operator+(const Point &p) const;
	const Point operator-(const Point &p) const;
	
	friend std::ostream & operator<<(std::ostream &out, const Point &p);
};

#endif
