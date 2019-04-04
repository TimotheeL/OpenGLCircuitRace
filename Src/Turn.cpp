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
	int ns = 10 + (int) (angle / 6) * (softness / 5);
	float rp, ar, a, cs, sn, xin = 0.0, xout = 0.0, zin = 0.0, zout = 0.0;
	Position vin, vout;
	for (int i = 0; i <= ns; i++) {
		rp = (i == 0 ? (float)i / ns + 0.00001 : (float)i / ns);
		ar = 2.0 * M_PI / (360.0 / angle);
		a = ar * rp;
		cs = cos(a);
		sn = -sin(a);

		(direction ? xin = softness * cs - softness - width / 2 : xin = softness * -cs + softness + width / 2);
		zin = softness * sn;
		(direction ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * -cs + softness + width / 2));
		zout = (softness + width) * sn;

		vin = rotate(xin, 0.0, zin);
		vin.x += pos.x; vin.y += pos.y; vin.z += pos.z; vin.angle -= a * 180 / M_PI;
		vertices.push_back(vin);

		vout = rotate(xout, 0.0, zout);
		vout.x += pos.x; vout.y += pos.y; vout.z += pos.z; vout.angle -= a * 180 / M_PI;
		vertices.push_back(vout);
	}
}

/* Bounding boxes generator */
void Turn::generateBoundingBoxes(void) {
	for (unsigned int i = 0; i < vertices.size() - 2; i++) {
		// Compute middle point
		float x = (vertices[i].x + vertices[i + 2].x) / 2;
		float y = (vertices[i].y + vertices[i + 2].y) / 2;
		float z = (vertices[i].z + vertices[i + 2].z) / 2;
		float angle = (vertices[i].angle + vertices[i + 2].angle) / 2;

		// Compute length
		float length = sqrt(
			powf(vertices[i + 2].x - vertices[i].x, 2)
			+ powf(vertices[i + 2].z - vertices[i].z, 2)
		);

		// Create the bounding box
		sideboxes.push_back(
			new Object(0.1, length, 2.0, new Position(x, y, z, angle))
		);
	}
}

// Drawer
void Turn::draw(void) {
	float colorTrack[4] = { 0.3, 0.3, 0.3, 1.0 };
	glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(pos.x, pos.y, pos.z);
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorTrack);
			glBegin(GL_QUAD_STRIP);
				glNormal3f(0.0F, 1.0F, 0.0F);
				for (unsigned int i = 0; i < vertices.size(); i++) {
					glVertex3f(vertices[i].x - pos.x, vertices[i].y - pos.y, vertices[i].z - pos.z);
				}
			glEnd();
		glPopMatrix();
		glPushMatrix();
			for (unsigned int i = 0; i < vertices.size(); i++) {
				if (i % 2 != 0) {
					glPushMatrix();
						float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
						float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
						glMaterialfv(GL_FRONT, GL_DIFFUSE, i % 3 == 0 ? white : red);
						glTranslatef(vertices[i].x - pos.x, vertices[i].y - pos.y, vertices[i].z - pos.z);
						glutSolidCube(1.0f);
					glPopMatrix();
				}
			}
		glPopMatrix();
	glPopMatrix();
}