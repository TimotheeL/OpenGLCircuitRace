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
TrackPart::TrackPart(void):
	width(7.0),
	pos(new Position())
{
	hitbox.update(&pos);
}

// 2-arguments constructor
TrackPart::TrackPart(float width, Position pos):
	width(width),
	pos(pos)
{
	hitbox.update(&this->pos);
}

// Copy constructor
TrackPart::TrackPart(TrackPart *p1):
	width(p1->getWidth()),
	pos(p1->getPosition()) 
{
	hitbox.update(&pos);
}

// Destructor
TrackPart::~TrackPart(void) {}

// Getters
float TrackPart::getWidth(void) {
	return width;
}

vector<Position> TrackPart::getVertices(void) {
	return vertices;
}

Position TrackPart::getPosition(void) {
	return pos;
}

vector<Object> *TrackPart::getSideboxes(void) {
	return &sideboxes;
}

// Setters
void TrackPart::setWidth(float width) {
	this->width = width;
}

// Degrees to radians conversion
float TrackPart::radians(float angle) {
	return (float) ((angle * M_PI) / 180.0);
}

// Rotate util function
Position TrackPart::rotate(float x, float y, float z) {
	float rx = cos(radians(pos.angle)) * x + sin(radians(pos.angle)) * z;
	float ry = y;
	float rz = - sin(radians(pos.angle)) * x + cos(radians(pos.angle)) * z;
	return new Position(rx, ry, rz, -pos.angle);
}

// Drawer
void TrackPart::draw(void) {}

void TrackPart::drawBoundingBoxes(void) {
	for (unsigned int i = 0; i < sideboxes.size(); i++) {
		sideboxes[i].draw();
	}
}

/* Compute vertices */
void TrackPart::computeVertices(void) {}

/* Basic bounding boxes generator for a track part */
void TrackPart::generateBoundingBoxes(void) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		sideboxes.push_back(new Object(1.0, 1.0, 1.0, &vertices[i]));
	}
}

/* Basic IsColliding resetter for a track part */
void TrackPart::resetIsColliding(void) {
	isColliding = false;
	for (unsigned int i = 0; i < sideboxes.size(); i++) {
		sideboxes[i].resetIsColliding();
	}
}