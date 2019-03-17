/*
	Racing game project - Tree class
	Represents a tree (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Tree.h"

// Regular constructor with 4 parameters
Tree::Tree(float wTrunk, float hTrunk, float wLeaves, float hLeaves) {
	this->wTrunk = wTrunk;
	this->hTrunk = hTrunk;
	this->wLeaves = wLeaves;
	this->hLeaves = hLeaves;
}

// Constructor generating random tree from given parameters
Tree::Tree(float wTrunkMin, float wTrunkMax, float hTrunkMin, float hTrunkMax, float wLeavesMin, float wLeavesMax, float hLeavesMin, float hLeavesMax) {
	this->wTrunk = wTrunkMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (wTrunkMax - wTrunkMin)));
	this->hTrunk = hTrunkMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hTrunkMax - hTrunkMin)));
	this->wLeaves = wLeavesMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (wLeavesMax - wLeavesMin)));
	this->hLeaves = hLeavesMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hLeavesMax - hLeavesMin)));
}

// Copy constructor
Tree::Tree(Tree *t1) {
	this->wTrunk = t1->getWTrunk();
	this->hTrunk = t1->getHTrunk();
	this->wLeaves = t1->getWLeaves();
	this->hLeaves = t1->getHLeaves();
}

// Destructor
Tree::~Tree(void) {}


// Getters
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

// Print
void Tree::print(void) {
	printf("%f, %f, %f, %f", wTrunk, hTrunk, wLeaves, hLeaves);
}