/*
	Racing game project - BoundingBox class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Objects.h>

/* Constructors */
Objects::Objects(float length, float width, float height, float x, float y, float z) {
	pos = new Position(x, y, z);
	hitbox = new BoundingBox(length, width, height, &pos);
}

Objects::Objects(BoundingBox b, Position pos) {
	hitbox = new BoundingBox(b);
	pos = new Position(pos);
}

Objects::Objects(Objects *o)
	:Objects(o->getBoundingBox(), o->getPos())
{}

Objects::Objects(void)
	:Objects(new BoundingBox(), new Position())
{}

/* Destructor */
Objects::~Objects(void) {}

/* Getters */
BoundingBox Objects::getBoundingBox(void) {
	return hitbox;
}

Position Objects::getPos(void) {
	return pos;
}

/* Draw */
void Objects::draw(void) {
	hitbox.draw();
}
