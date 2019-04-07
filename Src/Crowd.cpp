/*
	Racing game project - Patch class
	Represents a crowd (vector of spectators)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Crowd.h"

// Regular constructor
Crowd::Crowd(std::vector<Spectator> spectators) {
	this->spectators = spectators;
}

// Copy constructor
Crowd::Crowd(Crowd *c1) {
	this->spectators = c1->spectators;
}

Crowd::Crowd(void) {
}

// Destructor
Crowd::~Crowd(void) {}

// Getters
std::vector<Spectator> Crowd::getSpectators(void) {
	return this->spectators;
}

// Update spectators
void Crowd::update(void) {
	if (spectators.size() > 0) {
		unsigned int p = (rand() % static_cast<int>(spectators.size() * 100));
		if (p < spectators.size()) {
			spectators[p].setJumping();
		}
		for (unsigned int i = 0; i < spectators.size(); i++) {
			spectators[i].move();
		}
	}
}

// Draw each spectator
void Crowd::draw(void) {
	glPushMatrix();
	for (unsigned int i = 0; i < spectators.size(); i++) {
		spectators[i].draw();
	}
	glPopMatrix();
}

