/*
	Racing game project - Billboard class
	Represents a billboard (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Billboard.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Regular constructor
Billboard::Billboard(float xPos, float yPos, float zPos, float width, float height, float angle, float feetHeight) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->feetHeight = feetHeight;
}

// Copy constructor
Billboard::Billboard(Billboard *b1) {
	this->xPos = b1->xPos;
	this->yPos = b1->yPos;
	this->zPos = b1->zPos;
	this->width = b1->width;
	this->height = b1->height;
	this->angle = b1->angle;
	this->feetHeight = b1->feetHeight;
}

Billboard::Billboard(void)
	:Billboard(0.0, 0.0, 0.0, 3.0, 1.0, 0.0, 1.0)
{}

// Destructor
Billboard::~Billboard(void) {}

float Billboard::getXPos(void) {
	return xPos;
}

float Billboard::getYPos(void) {
	return yPos;
}

float Billboard::getZPos(void) {
	return zPos;
}

float Billboard::getAngle(void) {
	return angle;
}

float Billboard::getFeetHeight(void) {
	return feetHeight;
}

float Billboard::getWidth(void) {
	return width;
}

float Billboard::getHeight(void) {
	return height;
}


void Billboard::update(void) {
}

// Draw a billboard
void Billboard::draw(void) {
	float colorBoard[4] = { 0.8, 0.8, 0.8, 1.0 };
	float colorMetal[4] = { 0.6, 0.6, 0.6, 1.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBoard);
		glTranslatef(xPos, yPos, zPos);
		glRotatef(angle, 0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(0.0, feetHeight + height / 2, 0.05);
			glScalef(width, height, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorMetal);
		glPushMatrix();
			glTranslatef(-width / 2 + 0.07, feetHeight / 2, 0.0);
			glScalef(0.1, feetHeight + height, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(width / 2 - 0.07, feetHeight / 2, 0.0);
			glScalef(0.1, feetHeight + height, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, feetHeight + height / 2, 0.0);
			glScalef(width - 0.04, 0.1, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}


