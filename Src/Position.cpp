/*
	Racing game project - Position class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Position.h>

/* Constructors */
Position::Position(float cx, float cy, float cz, float cangle) {
	x = cx;
	y = cy;
	z = cz;
	angle = cangle;
}

Position::Position(float cx, float cy, float cz) :Position(cx, cy, cz, 0.0) { }

Position::Position(void):Position(0.0, 0.0, 0.0, 0.0) { }

Position::Position(Position *p) {
	x = p->x;
	y = p->y;
	z = p->z;
	angle = p->angle;
}

/* Destructor */
Position::~Position(void) { }