#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
protected:
	double m_x;
	double m_y;
	double m_z;
	
public:
	Point(double x, double y, double z);
	Point(const Point &p);
	
	double x();
	double y();
	double z();
	
	bool operator==(const Point &other) const;
	
	friend std::ostream & operator<<(std::ostream &out, const Point &p);
};

#endif