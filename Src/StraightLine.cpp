/*
	Racing game project - StraightLine class
	Represents a straight line as a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include "TrackPart.h"
#include "StraightLine.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Regular constructor
StraightLine::StraightLine(void):
	TrackPart(),
	length(7.0)
{}

// 3-arguments constructor
StraightLine::StraightLine(float width, float length, Position pos):
	TrackPart(width, pos),
	length(length)
{}

// Copy constructor
StraightLine::StraightLine(StraightLine *p1):
	TrackPart(p1->getWidth(), p1->getPosition()),
	length(p1->getLength()) {}

// Destructor
StraightLine::~StraightLine(void) {}

// Getters
float StraightLine::getLength(void) {
	return length;
}

// Setters
void StraightLine::setLength(float length) {
	this->length = length;
}

// Drawer
void StraightLine::draw(void) {
	glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(pos.x, 0.0, pos.z);
		glRotatef(pos.angle, 0.0, 1.0, 0.0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glNormal3f(0.0F, 1.0F, 0.0F);

				glVertex3f(-width / 2.0, 0.0, 0.0);
				Position v1 = rotate(-width / 2.0, 0.0, 0.0);
				v1.x += pos.x; v1.y += pos.y; v1.z += pos.z;
				vertices.push_back(v1);

				glVertex3f(width / 2.0, 0.0, 0.0);
				Position v2 = rotate(width / 2.0, 0.0, 0.0);
				v2.x += pos.x; v2.y += pos.y; v2.z += pos.z;
				vertices.push_back(v2);

				glVertex3f(width / 2.0, 0.0, - length);
				Position v3 = rotate(width / 2.0, 0.0, - length);
				v3.x += pos.x; v3.y += pos.y; v3.z += pos.z;
				vertices.push_back(v3);

				glVertex3f(-width / 2.0, 0.0, - length);
				Position v4 = rotate(-width / 2.0, 0.0, - length);
				v4.x += pos.x; v4.y += pos.y; v4.z += pos.z;
				vertices.push_back(v4);
			glEnd();
		glPopMatrix();
	glPopMatrix();
}