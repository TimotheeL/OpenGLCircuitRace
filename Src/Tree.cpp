/*
	Racing game project - Tree class
	Represents a tree (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Tree.h"

// Constructor
Tree::Tree(float xPos, float zPos, float wTrunk, float hTrunk, float wLeaves, float hLeaves) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->wTrunk = wTrunk;
	this->hTrunk = hTrunk;
	this->wLeaves = wLeaves;
	this->hLeaves = hLeaves;
}

// Copy constructor
Tree::Tree(Tree *t1) {
	this->xPos = t1->getXPos();
	this->zPos = t1->getZPos();
	this->wTrunk = t1->getWTrunk();
	this->hTrunk = t1->getHTrunk();
	this->wLeaves = t1->getWLeaves();
	this->hLeaves = t1->getHLeaves();
}

Tree::Tree(void)
	:Tree(0.0, 0.0, 0.5, 1.0, 1.5, 3.0)
{}

// Destructor
Tree::~Tree(void) {}

// Getters
float Tree::getXPos(void) {
	return xPos;
}

float Tree::getZPos(void) {
	return zPos;
}

float Tree::getWTrunk(void) {
	return wTrunk;
}

float Tree::getHTrunk(void) {
	return hTrunk;
}

float Tree::getWLeaves(void) {
	return wLeaves;
}

float Tree::getHLeaves(void) {
	return hLeaves;
}

// OpenGL code to draw the tree
void Tree::draw(void) {
	float colorTrunk[4] = { 0.5, 0.2, 0.18, 1.0 };
	float colorLeaves[4] = { 0.1, 0.5, 0.1, 1.0 };

	glPushMatrix();
		glTranslatef((GLfloat)xPos, -0.1, (GLfloat)zPos);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorTrunk);
			glTranslatef(0.0, hTrunk / 2, 0.0);
			glScalef(wTrunk, hTrunk, wTrunk);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorLeaves);
			glTranslatef(0.0, hTrunk + hLeaves / 2, 0.0);
			glScalef(wLeaves, hLeaves, wLeaves);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

// Print
void Tree::print(void) {
	printf("%f, %f, %f, %f, %f, %f", xPos, zPos, wTrunk, hTrunk, wLeaves, hLeaves);
}