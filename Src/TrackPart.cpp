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

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

// Regular constructor
TrackPart::TrackPart(void) {
	this->width = 7.0;
	this->pos = new Position();
}

// Copy constructor
TrackPart::TrackPart(TrackPart *p1) {
	this->width = p1->getWidth();
}
Position TrackPart::getPosition(void) {
	return pos;
}

// Destructor
TrackPart::~TrackPart(void) {}

// Getters
float TrackPart::getWidth(void) {
	return width;
}
std::vector<Position> TrackPart::getVertices(void) {
	return vertices;
}

// Setters
void TrackPart::setWidth(float width) {
	this->width = width;
}
// Degrees to radians conversion
float TrackPart::radians(float angle) {
	return (angle * M_PI) / 180.0;
}
// Rotate util function
Position TrackPart::rotate(float x, float y, float z) {
	float rx = cos(radians(pos.angle)) * x + sin(radians(pos.angle)) * z;
	float ry = y;
	float rz = - sin(radians(pos.angle)) * x + cos(radians(pos.angle)) * z;
	return new Position(rx, ry, rz, 0.0);
}

// Drawer
void TrackPart::draw(void) {}