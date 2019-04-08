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
	this->centerLeaves = hTrunk + hLeaves / 2;
	this->centerTrunk = hTrunk / 2;
}

// Copy constructor
Tree::Tree(Tree *t1) {
	this->xPos = t1->xPos;
	this->zPos = t1->zPos;
	this->wTrunk = t1->wTrunk;
	this->hTrunk = t1->hTrunk;
	this->wLeaves = t1->wLeaves;
	this->hLeaves = t1->hLeaves;
	this->centerLeaves = t1->centerLeaves;
	this->centerTrunk = t1->centerTrunk;
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
		glTranslatef(xPos, -0.1, zPos);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorTrunk);
			glTranslatef(0.0, centerTrunk, 0.0);
			glScalef(wTrunk, hTrunk, wTrunk);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorLeaves);
			glTranslatef(0.0, centerLeaves, 0.0);
			glScalef(wLeaves, hLeaves, wLeaves);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}
