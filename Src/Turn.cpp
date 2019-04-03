/*
	Racing game project - Turn class
	Represents a turn as a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include "TrackPart.h"
#include "Turn.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Regular constructor
Turn::Turn(void):
	TrackPart(),
	softness(7.0),
	angle(90.0),
	direction(true) 
{
	computeVertices();
	generateBoundingBoxes();
}

// 5-arguments constructor
Turn::Turn(float width, float softness, float angle, bool direction, Position pos):
	TrackPart(width, pos),
	softness(softness),
	angle(angle),
	direction(direction) 
{
	computeVertices();
	generateBoundingBoxes();
}

// Copy constructor
Turn::Turn(Turn *p1):
	TrackPart(p1->width, p1->pos),
	softness(p1->softness),
	angle(p1->angle),
	direction(p1->direction)
{
	computeVertices();
	generateBoundingBoxes();
}

// Destructor
Turn::~Turn(void) {}

// Getters
float Turn::getSoftness(void) {
	return softness;
}

float Turn::getAngle(void) {
	return angle;
}

bool Turn::getDirection(void) {
	return direction;
}

// Setters
void Turn::setSoftness(float softness) {
	this->softness = softness;
}

void Turn::setAngle(float angle) {
	this->angle = angle;
}

void Turn::setDirection(bool direction) {
	this->direction = direction;
}

// compute vertices to draw and compute collisions
void Turn::computeVertices(void) {
	int ns = 40;
	float rp, ar, a, cs, sn, xin = 0.0, xout = 0.0, zin = 0.0, zout = 0.0;
	Position vin, vout;
	for (int i = 0; i <= ns; i++) {
		rp = (i == 0 ? (float)i / ns + 0.00001 : (float)i / ns);
		ar = 2.0 * M_PI / (360.0 / angle);
		a = ar * rp;
		cs = cos(a);
		sn = -sin(a);

		(direction == true ? xin = softness * cs - softness - width / 2 : xin = softness * -cs + softness + width / 2);
		zin = softness * sn;
		(direction == true ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * -cs + softness + width / 2));
		zout = (softness + width) * sn;

		vin = rotate(xin, 0.0, zin);
		vin.x += pos.x; vin.y += pos.y; vin.z += pos.z;
		vertices.push_back(vin);

		vout = rotate(xout, 0.0, zout);
		vout.x += pos.x; vout.y += pos.y; vout.z += pos.z;
		vertices.push_back(vout);
	}
}

// Drawer
void Turn::draw(void) {
	glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(pos.x, pos.y, pos.z);
		//glRotatef(pos.angle, 0.0, 1.0, 0.0);
		glPushMatrix();
			glBegin(GL_QUAD_STRIP);
				glNormal3f(0.0F, 1.0F, 0.0F);

				for (unsigned int i = 0; i < vertices.size(); i++) {
					glVertex3f(vertices[i].x - pos.x, vertices[i].y - pos.y, vertices[i].z - pos.z);
				}
			glEnd();
		glPopMatrix();
	glPopMatrix();
}

/* Bounding boxes generator */
void Turn::generateBoundingBoxes(void) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		sideboxes.push_back(new Object(1.0, 1.0, 1.0, &vertices[i]));
	}
}