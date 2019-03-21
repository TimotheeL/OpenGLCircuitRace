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
StraightLine::StraightLine(void) {}

// 2-arguments constructor
StraightLine::StraightLine(float width, float length) {
	this->width = width;
	this->length = length;
}


// Copy constructor
StraightLine::StraightLine(StraightLine *p1):TrackPart(p1) {
	this->length = p1->getLength();
}

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

// Builder
void StraightLine::build(void) {
	glColor3f(0.25, 0.25, 0.25);
	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(0.0F, 1.0F, 0.0F);
		glVertex3f(-width / 2.0, 0.0, 0.0);
		glVertex3f(width / 2.0, 0.0, 0.0);
		glVertex3f(width / 2.0, length, 0.0);
		glVertex3f(-width / 2.0, length, 0.0);
	glEnd();
	glPopMatrix();
	glTranslatef(0.0, 0.0, -length);
}