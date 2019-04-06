/*
	Racing game project - Patch class
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

#include "Patch.h"
#include "Tree.h"

// Regular constructor
Patch::Patch(float xPos, float zPos, float size, int nbTrees) {
	this->xPos = xPos;
	this->zPos = zPos;
	this->size = size;
	this->nbTrees = nbTrees;
	for (int i = 0; i < nbTrees; i++) {
		float xPos = this->xPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / size));
		float zPos = this->zPos + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / -size));
		float wTrunk = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0));
		float hTrunk = 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4.0));
		float wLeaves = 3.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.0));
		float hLeaves = 3.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4.0));
		Tree tree = new Tree(xPos, zPos, wTrunk, hTrunk, wLeaves, hLeaves);
		trees.push_back(tree);
	}
}

// Copy constructor
Patch::Patch(Patch *p1) {
	this->xPos = p1->xPos;
	this->zPos = p1->zPos;
	this->size = p1->size;
	this->nbTrees = p1->nbTrees;
	this->trees = p1->trees;
}

Patch::Patch(void)
	:Patch(0.0, 0.0, 32.0, 3)
{}

// Destructor
Patch::~Patch(void) {}

float Patch::getXPos(void) {
	return this->xPos;
}
float Patch::getZPos(void) {
	return this->zPos;
}
float Patch::getSize(void) {
	return this->size;
}
int Patch::getNbTrees(void) {
	return this->nbTrees;
}

// Draw a patch
void Patch::draw(void) {
	float colorLeaves[4] = { 0.1, 0.4, 0.1, 1.0 };

	glPushMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorLeaves);
			glBegin(GL_QUADS);
				glNormal3f(0.0F, 1.0F, 0.0F);
				glVertex3f(xPos, -0.1, zPos);
				glVertex3f(xPos + size, -0.1, zPos);
				glVertex3f(xPos + size, -0.1, zPos - size);
				glVertex3f(xPos, -0.1, zPos - size);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			for (int i = 0; i < nbTrees; i++) {
				trees[i].draw();
			}
		glPopMatrix();
	glPopMatrix();
}

