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

// Regular constructor
Turn::Turn(void):TrackPart() {
	this->softness = 7.0;
	this->angle = 90.0;
	this->direction = true;
}

// 5-arguments constructor
Turn::Turn(float width, float softness, float angle, bool direction, Position pos) {
	this->width = width;
	this->softness = softness;
	this->angle = angle;
	this->direction = direction;
	this->pos = pos;
}

// Copy constructor
Turn::Turn(Turn *p1):TrackPart(p1) {
	this->width = width;
	this->softness = softness;
	this->angle = angle;
	this->direction = direction;
	this->pos = pos;
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

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Drawer
void Turn::draw(void) {
	glPushMatrix();
		glRotatef(pos.angle, 0.0, 1.0, 0.0);
		int ns = 40;
		glColor3f(0.5, 0.5, 0.5);
		glNormal3f(0.0F, 1.0F, 0.0F);

		glBegin(GL_QUAD_STRIP);
		float rp, ar, a, cs, sn, xin = 0.0, xout = 0.0, zin = 0.0, zout = 0.0;
		Position vin, vout;
		for (int i = 0; i <= ns; i++) {
			rp = (i == 0 ? (float)i / ns + 0.00001 : (float)i / ns);
			ar = 2.0*3.1415926535897932384626433832795 / (360.0 / angle);
			a = ar*rp;
			cs = cos(a);
			sn = -sin(a);

			(direction == true ? xin = softness * cs - softness - width / 2 : xin = softness * - cs + softness + width / 2);
			zin = softness * sn;
			(direction == true ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * - cs + softness + width / 2));
			zout = (softness + width) * sn;

			glVertex3f(xin + pos.x, pos.y, zin + pos.z);
			vin = rotate(xin, 0.0, zin);
			vin.x += pos.x; vin.y += pos.y; vin.z += pos.z;
			vertices.push_back(vin);

			glVertex3f(xout + pos.x, pos.y, zout + pos.z);
			vout = rotate(xout, 0.0, zout);
			vout.x += pos.x; vout.y += pos.y; vout.z += pos.z;
			vertices.push_back(vout);
		}
		glEnd();
	glPopMatrix();
}