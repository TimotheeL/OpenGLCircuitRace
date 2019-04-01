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

// Constructor generating random tree from given parameters
Tree::Tree(float xPos, float zPos, float wTrunkMin, float wTrunkMax, float hTrunkMin, float hTrunkMax, float wLeavesMin, float wLeavesMax, float hLeavesMin, float hLeavesMax) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->wTrunk = wTrunkMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (wTrunkMax - wTrunkMin)));
	this->hTrunk = hTrunkMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hTrunkMax - hTrunkMin)));
	this->wLeaves = wLeavesMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (wLeavesMax - wLeavesMin)));
	this->hLeaves = hLeavesMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hLeavesMax - hLeavesMin)));
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
	glTranslatef((GLfloat)xPos, 0.0, (GLfloat)zPos);
	glPushMatrix();
	glTranslatef(0.0, hTrunk / 2, 0.0);
	glScalef(wTrunk, hTrunk, wTrunk);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorTrunk);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, hTrunk + hLeaves / 2, 0.0);
	glScalef(wLeaves, hLeaves, wLeaves);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorLeaves);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}

// Print
void Tree::print(void) {
	printf("%f, %f, %f, %f, %f, %f", xPos, zPos, wTrunk, hTrunk, wLeaves, hLeaves);
}