/*
	Racing game project - TrackPart class
	Represents a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "TrackPart.h"

// Regular constructor
TrackPart::TrackPart(void) {
	this->width = 7.0;
}

// Copy constructor
TrackPart::TrackPart(TrackPart *p1) {
	this->width = p1->getWidth();
}

// Destructor
TrackPart::~TrackPart(void) {}

// Getters
float TrackPart::getWidth(void) {
	return width;
}
// Setters
void TrackPart::setWidth(float width) {
	this->width = width;
}