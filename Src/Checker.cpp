/*
	Racing game project - Checker class
	Represents a checker pattern (Used for the start line)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Checker.h"

// Regular constructor
Checker::Checker(float xPos, float zPos, float squareSize, int width, int height) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->squareSize = squareSize;
	this->width = width;
	this->height = height;
}

// Copy constructor
Checker::Checker(Checker *c1) {
	this->xPos = c1->xPos;
	this->zPos = c1->zPos;
	this->squareSize = c1->squareSize;
	this->width = c1->width;
	this->height = c1->height;
}

Checker::Checker(void)
	:Checker(0.0, 0.0, 4.0, 10.0, 1.0)
{}

// Destructor
Checker::~Checker(void) {}


// Getters
float Checker::getXPos(void) {
	return this->xPos;
}
float Checker::getZPos(void) {
	return this->zPos;
}
float Checker::getSize(void) {
	return this->squareSize;
}
int Checker::getWidth(void) {
	return this->width;
}

int Checker::getHeight(void) {
	return this->height;
}

// Draw a checker pattern
void Checker::draw(void) {
	float colorChecker[4] = { 1.0, 1.0, 1.0, 1.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorChecker);
		glBegin(GL_QUADS);
			glNormal3f(0.0F, 1.0F, 0.0F);
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (j % 2 == 0 && i % 2 == 0 || j % 2 == 1 && i % 2 == 1) {
						glVertex3f(xPos + j * squareSize, 0.01, zPos - i * squareSize);
						glVertex3f(xPos + j * squareSize + squareSize, 0.01, zPos - i * squareSize);
						glVertex3f(xPos + j * squareSize + squareSize, 0.01, zPos - i * squareSize + squareSize);
						glVertex3f(xPos + j * squareSize, 0.01, zPos - i * squareSize + squareSize);
					}
				}
			}
		glEnd();
	glPopMatrix();
}
