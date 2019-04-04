/*
	Racing game project - Bleachers class
	Represents bleachers with spectators (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Bleachers.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Regular constructor
Bleachers::Bleachers(float xPos, float zPos, int width, int depth, float angle, float filling) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->width = width;
	this->depth = depth;
	this->angle = angle;
	this->filling = filling;

	float rad = angle * M_PI / 180;
	float centerX = xPos + width / 2;
	float centerZ = zPos - depth / 2;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < depth; j++) {
			if (static_cast <float> (rand()) < filling) {
				float specX = (zPos * j - centerZ) * sin(rad) + (xPos * i - centerX) * cos(rad);
				float specZ = (zPos * j - centerZ) * cos(rad) - (xPos * i - centerX) * sin(rad);
				spectators.push_back(new Spectator(specX, j * 0.5 + 0.5, specZ, static_cast <float> (rand()), static_cast <float> (rand()), static_cast <float> (rand()), static_cast <float> (rand()) < 0.5));
			}
		}
	}
}

// Copy constructor
Bleachers::Bleachers(Bleachers *b1) {
	this->xPos = b1->xPos;
	this->zPos = b1->zPos;
	this->width = b1->width;
	this->depth = b1->depth;
	this->angle = b1->angle;
	this->filling = b1->filling;
	this->spectators = b1->spectators;
}

Bleachers::Bleachers(void)
	:Bleachers(0.0, 0.0, 10, 3, 0.0, 1.0)
{}

// Destructor
Bleachers::~Bleachers(void) {}

float Bleachers::getXPos(void) {
	return xPos;
}

float Bleachers::getZPos(void) {
	return zPos;
}

float Bleachers::getAngle(void) {
	return angle;
}

float Bleachers::getFilling(void) {
	return filling;
}

int Bleachers::getWidth(void) {
	return width;
}

int Bleachers::getDepth(void) {
	return depth;
}

std::vector<Spectator> Bleachers::getSpectators(void) {
	return spectators;
}

// Update spectators on a patch
void Bleachers::update(void) {
	for (unsigned int i = 0; i < spectators.size(); i++) {
		spectators[i].move();
		if (static_cast <float> (rand()) < 0.2) {
			spectators[i].setJumping();
		}
	}
}

// Draw a patch
void Bleachers::draw(void) {
	glPushMatrix();
	float colorBleachers[4] = { 0.3, 0.3, 0.3, 1.0 };
	int i = 0; 
	int j = 0;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBleachers);
		for (int i = 0; i < depth; i++) {
			glPushMatrix();
				glTranslatef(xPos + (float)(width / 2), i * 0.25 + 0.25, zPos - i * 0.5 - 0.5f);
				glRotatef(angle, 0.0, 1.0, 0.0);
				glScalef((float)width, 0.5 * i + 0.5, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
		for (unsigned int i = 0; i < spectators.size(); i++) {
			spectators[i].draw();
		}
	glPopMatrix();
}

