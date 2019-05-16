/*
	Racing game project - Spectator class
	Represents a spectator (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Spectator.h"

// Regular constructors
Spectator::Spectator(float xPos, float yPos, float zPos, float color[3], bool jumping) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->currYPos = yPos;
	this->jumping = jumping;
	this->goingUp = true;
	this->bodyPos = yPos + 0.6;
	this->headPos = yPos + 1.6;

	for (int i = 0; i < 3; i++) {
		this->color[i] = color[i];
	}
}

Spectator::Spectator(float xPos, float yPos, float zPos, float red, float green, float blue, bool jumping) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->currYPos = yPos;
	this->jumping = jumping;
	this->goingUp = true;
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
}

// Copy constructor
Spectator::Spectator(Spectator *s1) {
	this->xPos = s1->xPos;
	this->yPos = s1->yPos;
	this->zPos = s1->zPos;
	this->currYPos = s1->currYPos;
	this->jumping = s1->jumping;
	this->goingUp = s1->goingUp;
	this->bodyPos = s1->bodyPos;
	this->headPos = s1->headPos;

	for (int i = 0; i < 3; i++) {
		this->color[i] = s1->color[i];
	}
}

Spectator::Spectator(void)
	:Spectator(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, false)
{}

// Destructor
Spectator::~Spectator(void) {}

// Getters
float Spectator::getXPos(void) {
	return xPos;
}

float Spectator::getYPos(void) {
	return yPos;
}

float Spectator::getZPos(void) {
	return zPos;
}

float Spectator::getCurrYPos(void) {
	return currYPos;
}

bool Spectator::getJumping(void) {
	return jumping;
}

// Setters
void Spectator::setJumping(void) {
	jumping = !jumping;
}

void Spectator::move(void) {
	if (jumping || currYPos > yPos) {
		if (currYPos > yPos + 1.0) {
			goingUp = false;
		}
		else if (currYPos < yPos) {
			goingUp = true;
		}

		currYPos += goingUp ? 0.05 : -0.05;
		bodyPos = currYPos + 0.6;
		headPos = currYPos + 1.6;
	}
}

void Spectator::draw(void) {
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
		glPushMatrix();
			glTranslatef(xPos, bodyPos, zPos);
			glScalef(0.6, 1.2, 0.6);
			glutSolidSphere(0.5, 5, 4);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(xPos, headPos, zPos);
			glutSolidSphere(0.3, 5, 4);
		glPopMatrix();
	glPopMatrix();
}