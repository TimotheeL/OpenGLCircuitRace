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
{
	computeVertices();
	generateBoundingBoxes();
}

// 3-arguments constructor
StraightLine::StraightLine(float width, float length, Position pos):
	TrackPart(width, pos),
	length(length)
{
	computeVertices();
	generateBoundingBoxes();
}

// Copy constructor
StraightLine::StraightLine(StraightLine *p1):
	TrackPart(p1->getWidth(), p1->getPosition()),
	length(p1->getLength()) 
{
	computeVertices();
	generateBoundingBoxes();
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

// compute vertices to draw and compute collisions
void StraightLine::computeVertices(void) {
	Position v1 = rotate(-width / 2.0, 0.0, 0.0);
	v1.x += pos.x; v1.y += pos.y; v1.z += pos.z;
	vertices.push_back(v1);

	Position v2 = rotate(width / 2.0, 0.0, 0.0);
	v2.x += pos.x; v2.y += pos.y; v2.z += pos.z;
	vertices.push_back(v2);

	Position v3 = rotate(width / 2.0, 0.0, -length);
	v3.x += pos.x; v3.y += pos.y; v3.z += pos.z;
	vertices.push_back(v3);

	Position v4 = rotate(-width / 2.0, 0.0, -length);
	v4.x += pos.x; v4.y += pos.y; v4.z += pos.z;
	vertices.push_back(v4);
}

/* Bounding boxes generator */
void StraightLine::generateBoundingBoxes(void) {
	Position right = rotate((width / 2.0) + 0.05, 0.0, -length / 2.0);
	right.x += pos.x; right.y += pos.y; right.z += pos.z;

	Position left = rotate((-width / 2.0) - 0.05, 0.0, -length / 2.0);
	left.x += pos.x; left.y += pos.y; left.z += pos.z;

	sideboxes.push_back(new Object(0.1, length, 2.0, new Position(right)));
	sideboxes.push_back(new Object(0.1, length, 2.0, new Position(left)));
}

// Drawer
void StraightLine::draw(void) {
	float colorTrack[4] = { 0.15, 0.15, 0.15, 1.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorTrack);
		glTranslatef(pos.x, pos.y, pos.z);
		glPushMatrix();
			glBegin(GL_QUADS);
				glNormal3f(0.0F, 1.0F, 0.0F);

				for (unsigned int i = 0; i < vertices.size(); i++) {
					glVertex3f(vertices[i].x - pos.x, vertices[i].y - pos.y, vertices[i].z - pos.z);
				}
			glEnd();
		glPopMatrix();
	glPopMatrix();
}