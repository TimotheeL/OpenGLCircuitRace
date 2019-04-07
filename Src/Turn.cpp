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
	generateBoundingBoxes(0.5);
}

// 5-arguments constructor
Turn::Turn(float width, float softness, float angle, bool direction, Position pos):
	TrackPart(width, pos),
	softness(softness),
	angle(angle),
	direction(direction) 
{
	computeVertices();
	generateBoundingBoxes(0.5);
}

// Copy constructor
Turn::Turn(Turn *p1):
	TrackPart(p1->width, p1->pos),
	softness(p1->softness),
	angle(p1->angle),
	direction(p1->direction)
{
	computeVertices();
	generateBoundingBoxes(0.5);
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
	float rp, ar, a, cs, sn, xin = 0.0, xout = 0.0, zin = 0.0, zout = 0.0, xtire = 0.0, ztire = 0.0;
	Position vin, vout, tire;

	ar = 2.0 * M_PI / (360.0 / angle);

	for (int i = 0; i <= ns; i++) {
		rp = (i == 0 ? (float)i / ns + 0.00001 : (float)i / ns);
		a = ar * rp;
		cs = cos(a);
		sn = -sin(a);

		(direction ? xin = softness * cs - softness - width / 2 : xin = softness * -cs + softness + width / 2);
		zin = softness * sn;

		(direction ? xout = ((softness + width) * cs - softness - width / 2) : xout = ((softness + width) * -cs + softness + width / 2));
		zout = (softness + width) * sn;

		(direction ? xtire = ((softness + width + 1.0) * cs - softness - (width + 1.0) / 2) : xtire = ((softness + width + 1.0) * -cs + softness + (width + 1.0) / 2));
		ztire = (softness + width + 1.0) * sn;

		vin = rotate(xin, 0.0, zin);
		vin.x += pos.x; vin.y += pos.y; vin.z += pos.z;
		vin.angle -= (float) (a * 180.0 / M_PI);
		vertices.push_back(vin);

		vout = rotate(xout, 0.0, zout);
		vout.x += pos.x; vout.y += pos.y; vout.z += pos.z;
		vout.angle -= (float) (a * 180.0 / M_PI);
		vertices.push_back(vout);

		tire = rotate(xtire, 0.0, ztire);
		tire.x += pos.x; tire.y += pos.y; tire.z += pos.z;
		tire.angle -= (float)(a * 180.0 / M_PI);
		tires.push_back(tire);
	}
}

/* Bounding boxes generator */
void Turn::generateBoundingBoxes(float offset) {
	for (unsigned int i = 0; i < vertices.size() - 2; i++) {
		// Compute middle point
		float x = (vertices[i].x + vertices[i + 2].x) / 2;
		float y = (vertices[i].y + vertices[i + 2].y) / 2;
		float z = (vertices[i].z + vertices[i + 2].z) / 2;
		float a = (vertices[i].angle + vertices[i + 2].angle) / 2;

		// Correct the angle if the direction is false
		if (!direction) {
			a += (pos.angle * 2);
		}
		
		// Shift point with the offset
		float radangle = a / 180 * M_PI;			
		if (i % 2) {
			(direction ? x += cos(radangle) * offset : x += -(cos(radangle) * offset));
			z += sin(radangle) * offset;
		}
		else {
			(direction ? x += cos(radangle) * -offset : x += -(cos(radangle) * -offset));
			z += sin(radangle) * -offset;
		}

		// Compute length
		float length = sqrt(
			powf(vertices[i + 2].x - vertices[i].x, 2)
			+ powf(vertices[i + 2].z - vertices[i].z, 2)
		);

		// Reverse angle if the direction is false
		if (!direction) { a = -a; }

		// Create the bounding box
		sideboxes.push_back(
			new Object(offset * 2, length, 2.0, new Position(x, y, z, a))
		);
	}
}

// Util function to draw a cylindre
void Turn::mySolidCylindre(double hauteur, double rayon, int ns) {
	GLboolean nm = glIsEnabled(GL_NORMALIZE);
	if (!nm) {
		glEnable(GL_NORMALIZE);
	}

	float normale[4];
	glGetFloatv(GL_CURRENT_NORMAL, normale);

	glPushMatrix();
		hauteur /= 2.0F;
		glBegin(GL_QUAD_STRIP);
			for (int i = 0; i <= ns; i++) {
				float a = (2 * M_PI*i) / ns;
				float cs = cos(a);
				float sn = -sin(a);
				glNormal3f(cs, 0.0F, sn);
				float x = rayon * cs;
				float z = rayon * sn;
				glVertex3f(x, hauteur, z);
				glVertex3f(x, -hauteur, z);
			}
		glEnd();

		glBegin(GL_POLYGON);
		for (int i = 0; i <= ns; i++) {
			float a = (2 * M_PI*i) / ns;
			float cs = cos(a);
			float sn = -sin(a);
			glNormal3f(cs, 1.0F, sn);
			float x = rayon * cs;
			float z = rayon * sn;
			glVertex3f(x, hauteur, z);
		}
		glEnd();
	glPopMatrix();

	glNormal3f(normale[0], normale[1], normale[2]);
	if (!nm) {
		glDisable(GL_NORMALIZE);
	}
}

// Drawer
void Turn::draw(void) {
	float colorTrack[4] = { 0.15, 0.15, 0.15, 1.0 };
	glPushMatrix();
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
			for (unsigned int i = 0; i < tires.size(); i++) {
				if (i % 2 != 0) {
					glPushMatrix();
						float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
						float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
						glMaterialfv(GL_FRONT, GL_DIFFUSE, i % 3 == 0 ? white : red);
						glTranslatef(tires[i].x - pos.x, tires[i].y - pos.y, tires[i].z - pos.z);
						mySolidCylindre(1.0, 0.5, 8.0);
					glPopMatrix();
				}
			}
		glPopMatrix();
	glPopMatrix();
}