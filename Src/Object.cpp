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

#include <Object.h>

/* Constructors */
Object::Object(float length, float width, float height, float x, float y, float z) {
	pos = new Position(x, y, z);
	hitbox = new BoundingBox(length, width, height, &pos);
}

Object::Object(float length, float width, float height)
	:Object(length, width, height, 0.0, 0.0, 0.0)
{}

Object::Object(BoundingBox b, Position pos) {
	pos = new Position(pos);
	hitbox = new BoundingBox(b);
}

Object::Object(Object *o)
	:Object(o->getBoundingBox(), o->getPos())
{}

Object::Object(void)
	:Object(new BoundingBox(), new Position())
{}

/* Destructor */
Object::~Object(void) {}

/* Getters */
BoundingBox Object::getBoundingBox(void) {
	return hitbox;
}

Position Object::getPos(void) {
	return pos;
}

/* Draw */
void Object::draw(void) {
	hitbox.draw();
}

/* Collision test between this object and another object */
// Y COORDINATES AREN'T CHECKED
// Wrong checks, replace everything by the Separating Axis Theorem
void Object::collisionTest(Object *o) {
	// Get min and max coordinates to properly test collision
	float xmin1 = hitbox.points[0].x; 
	float xmax1 = hitbox.points[0].x;
	float zmin1 = hitbox.points[0].z;
	float zmax1 = hitbox.points[0].z;

	float xmin2 = o->hitbox.points[0].x;
	float xmax2 = o->hitbox.points[0].x;
	float zmin2 = o->hitbox.points[0].z;
	float zmax2 = o->hitbox.points[0].z;

	for (int i = 1; i < 4; i++) {
		if (hitbox.points[i].x < xmin1) {
			xmin1 = hitbox.points[i].x;
		}

		if (hitbox.points[i].x > xmax1) {
			xmax1 = hitbox.points[i].x;
		}

		if (hitbox.points[i].z < zmin1) {
			zmin1 = hitbox.points[i].z;
		}

		if (hitbox.points[i].z > zmax1) {
			zmax1 = hitbox.points[i].z;
		}

		if (o->hitbox.points[i].x < xmin2) {
			xmin2 = o->hitbox.points[i].x;
		}

		if (o->hitbox.points[i].x > xmax2) {
			xmax2 = o->hitbox.points[i].x;
		}

		if (o->hitbox.points[i].z < zmin2) {
			zmin2 = o->hitbox.points[i].z;
		}

		if (o->hitbox.points[i].z > zmax2) {
			zmax2 = o->hitbox.points[i].z;
		}
	}
	
	/* Test collision */
	if ((((xmin1 > xmin2 && xmin1 < xmax2) || (xmax1 > xmin2 && xmax1 < xmax2)) 
		&& ((zmin1 > zmin2 && zmin1 < zmax2) || (zmax1 > zmin2 && zmax1 < zmax2)))
		|| (((xmin2 > xmin1 && xmin2 < xmax1) || (xmax2 > xmin1 && xmax2 < xmax1)) 
			&& ((zmin2 > zmin1 && zmin2 < zmax1) || (zmax2 > zmin1 && zmax2 < zmax1)))
		|| ((xmin2 > xmin1 && xmax2 < xmax1 && zmin1 > zmin2 && zmax1 < zmax2))
		|| ((xmin1 > xmin2 && xmax1 < xmax2 && zmin2 > zmin1 && zmax2 < zmax1)))
	{
		printf("[%d]collision with object %d\n", rand(), o);
	}
}