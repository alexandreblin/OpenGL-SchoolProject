#ifndef OBJECT_H
#define OBJECT_H

#ifdef __MACH__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Point.h"
#include "Vector.h"
#include "Angle.h"

class Object {
protected:
	Point m_position;
	Angle m_angle;
	Vector m_scale;

public:
    Object(Point pos = Point(0, 0, 0), Angle angle = Angle(0, 0, 0), Vector scale = Vector(1, 1, 1));

	Point & position();
	Angle & angle();

	virtual void draw(bool keepMatrix = false) = 0;
};

#endif
