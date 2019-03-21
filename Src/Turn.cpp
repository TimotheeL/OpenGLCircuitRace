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
	this->direction = 'l';
}

// 4-arguments constructor
Turn::Turn(float width, float softness, float angle, char direction) {
	this->width = width;
	this->softness = softness;
	this->angle = angle;
	this->direction = direction;
}


// Copy constructor
Turn::Turn(Turn *p1):TrackPart(p1) {
	this->width = width;
	this->softness = softness;
	this->angle = angle;
	this->direction = direction;
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
char Turn::getDirection(void) {
	return direction;
}

// Setters
void Turn::setSoftness(float softness) {
	this->softness = softness;
}
void Turn::setAngle(float angle) {
	this->angle = angle;
}
void Turn::setDirection(char direction) {
	this->direction = direction;
}

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Drawer
void Turn::draw(void) {
	int ns = 40;
	//glColor3f(0.5, 0.5, 0.5);
	//glBegin(GL_QUAD_STRIP);
	//glNormal3f(0.0F, 1.0F, 0.0F);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= ns; i++) {
		float rp = (float)i / ns;
		float ar = 2.0*3.1415926535897932384626433832795 / (360.0 / angle);
		float a = ar*rp;
		float cs = cos(a);
		float sn = -sin(a);

		float xin, zin, xout, zout;
		(direction == 'l' ? xin = softness * cs - softness - width / 2 : xin = softness * -cs + softness + width / 2);
		//xin = softness * cs - softness - width / 2;
		zin = softness * sn;
		(direction == 'l' ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * - cs + softness + width / 2));
		//xout = ((softness + width) * cs - softness - width / 2);
		zout = (softness + width) * sn;


		glVertex3f(xin, 0.0, zin);
		glVertex3f(xout, 0.0, zout);
	}
	/* for (int i = 0; i <= 20; i++) {
		float rp = (float)i / 20;
		float ar = 2.0*M_PI / (360.0 / angle);
		float a = ar * rp;
		float cs = cos(a);
		float sn = -sin(a);

		float xin, zin, xout, zout;
		//(direction == 'l' ? xin = softness * cs - softness - width / 2 : xin = softness * cs + softness + width / 2);
		xin = softness * cs - softness - width / 2;
		zin = softness * sn;
		//(direction == 'l' ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * cs + softness + width / 2));
		xout = ((softness + width) * cs - softness - width / 2);
		zout = (softness + width) * sn;

		glVertex3f(xin, 0.0, zin);
		glVertex3f(xout, 0.0, zout);
	} */
	glEnd();
}