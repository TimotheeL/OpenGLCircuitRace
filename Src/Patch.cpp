/*
	Racing game project - Patch class
	Represents a patch of grass (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Patch.h"
#include "Tree.h"

// Regular constructor
Patch::Patch(float xPos, float zPos, float width, float height, int nbTrees, int nbSpectators, bool drawGrass) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->width = width;
	this->height = height;
	this->drawGrass = drawGrass;
	this->nbTrees = nbTrees;
	for (int i = 0; i < nbTrees; i++) {
		float xPos = this->xPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / width));
		float zPos = this->zPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / -height));
		float wTrunk = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));
		float hTrunk = 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4.0));
		float wLeaves = 3.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.0));
		float hLeaves = 3.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4.0));
		Tree tree = new Tree(xPos, zPos, wTrunk, hTrunk, wLeaves, hLeaves);
		trees.push_back(tree);
	}
	for (int i = 0; i < nbSpectators; i++) {
		float specX = xPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / width));
		float specZ = zPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / -height));
		spectators.push_back(new Spectator(specX, 0.0, specZ, (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), false));
	}
	this->xPos2 = xPos + width;
	this->zPos2 = zPos - height;
}


// Copy constructor
Patch::Patch(Patch *p1) {
	this->xPos = p1->xPos;
	this->zPos = p1->zPos;
	this->width = p1->width;
	this->width = p1->height;
	this->nbTrees = p1->nbTrees;
	this->trees = p1->trees;
	this->spectators = p1->spectators;
	this->xPos2 = p1->xPos2;
	this->zPos2 = p1->zPos2;
	this->drawGrass = p1->drawGrass;
}

Patch::Patch(void)
	:Patch(0.0, 0.0, 32.0, 32.0, 3, 0, true)
{}

// Destructor
Patch::~Patch(void) {}

float Patch::getXPos(void) {
	return this->xPos;
}
float Patch::getZPos(void) {
	return this->zPos;
}
float Patch::getWidth(void) {
	return this->width;
}
float Patch::getHeight(void) {
	return this->height;
}
int Patch::getNbTrees(void) {
	return this->nbTrees;
}
bool Patch::getDrawGrass(void) {
	return this->drawGrass;
}

// Draw a patch
void Patch::draw(void) {
	float colorLeaves[4] = { 0.1, 0.4, 0.1, 1.0 };

	glPushMatrix();
		if (drawGrass) {
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_DIFFUSE, colorLeaves);
				glBegin(GL_QUADS);
					glNormal3f(0.0F, 1.0F, 0.0F);
					glVertex3f(xPos, -0.1, zPos);
					glVertex3f(xPos2, -0.1, zPos);
					glVertex3f(xPos2, -0.1, zPos2);
					glVertex3f(xPos, -0.1, zPos2);
				glEnd();
			glPopMatrix();
		}
		glPushMatrix();
			for (int i = 0; i < nbTrees; i++) {
				trees[i].draw();
			}
		glPopMatrix();
		glPushMatrix();
			Crowd::draw();
		glPopMatrix();
	glPopMatrix();
}

