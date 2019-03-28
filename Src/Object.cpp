/*
	Racing game project - BoundingBox class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Object.h>

/* Constructors */
Object::Object(float length, float width, float height, float x, float y, float z) {
	pos = new Position(x, y, z);
	hitbox = new BoundingBox(length, width, height, &pos);
	this->length = length;
	this->width = width;
	this->height = height;
	isColliding = false;
}

Object::Object(float length, float width, float height)
	:Object(length, width, height, 0.0, 0.0, 0.0)
{}

Object::Object(Object *o)
{
	pos = new Position(o->getPos());
	hitbox = new BoundingBox(o->getBoundingBox());
	length = o->length;
	width = o->width;
	height = o->height;
	isColliding = o->isColliding;
}

Object::Object(void)
	:Object(5.0, 5.0, 5.0, 0.0, 0.0, 0.0)
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

float Object::getLength(void) {
	return length;
}

float Object::getWidth(void) {
	return width;
}

float Object::getHeight(void) {
	return height;
}

bool Object::getIsColliding(void) {
	return isColliding;
}

/* Setters */
void Object::resetIsColliding(void) {
	isColliding = false;
}

/* Draw */
void Object::draw(void) {
	hitbox.draw();
}

/* Collision test between this object and another object
 * using the Separating Axis Theorem (SAT)
 * Y VALUES AREN'T TESTED
 * Implemented thanks to : http://www.dyn4j.org/2010/01/sat/
 */
void Object::collisionTestSAT(Object *o) {
	/* An axis is a normal of a side of the object 
	 * We don't use the Y parameter of our bounding boxes,
	 * so we'll check only 4 axes like in a 2D world
	 * An axis is a 2D normalized vector
	 */
	float axes[4][2];  // Axes for this object
	float oaxes[4][2]; // Axes for the other object

	/* Get the axes */
	getAxesSAT(axes, &hitbox);
	getAxesSAT(oaxes, &o->hitbox);

	/* A projection is composed of [0] = min and [1] = max.
	 * Thoses are the result of the projection of the points of a bounding box
	 * on one of the axis previously found
	 */
	float projection[2];
	float oprojection[2];

	/* For every axis found for the first object */
	for (int i = 0; i < 4; i++) {
		/* Get the axis */
		float axis[2] = { axes[i][0], axes[i][1] };

		/* Do the projection for both objects */
		projectObjectSAT(axis, &hitbox, projection);
		projectObjectSAT(axis, &o->hitbox, oprojection);

		/* Check projections overlapping */
		if (!((projection[0] >= oprojection[0] && projection[1] <= oprojection[1])
			|| (projection[1] >= oprojection[0] && projection[1] <= oprojection[1])
			|| (oprojection[0] >= projection[0] && oprojection[0] <= projection[1])
			|| (oprojection[1] >= projection[0] && oprojection[1] <= projection[1])
		)) {
			/* If there's no overlap, there's no collision, return
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}

			return;
		}
	}

	/* For every axis found for the second object */
	for (int i = 0; i < 4; i++) {
		/* Get the axis */
		float axis[2] = { oaxes[i][0], oaxes[i][1] };

		/* Do the projection for both objects */
		projectObjectSAT(axis, &hitbox, projection);
		projectObjectSAT(axis, &o->hitbox, oprojection);

		/* Check projections overlapping */
		if (!((projection[0] >= oprojection[0] && projection[1] <= oprojection[1])
			|| (projection[1] >= oprojection[0] && projection[1] <= oprojection[1])
			|| (oprojection[0] >= projection[0] && oprojection[0] <= projection[1])
			|| (oprojection[1] >= projection[0] && oprojection[1] <= projection[1])
		)) {
			/* If there's no overlap, there's no collision, return
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}
			
			return;
		}
	}

	/* If we haven't returned, it means that all the projections overlap
	 * so there is a collision between the objects.
	 * Change the color if it's the first collision
	 */
	if (!isColliding) {
		isColliding = true;
		hitbox.setColor(0.0, 1.0, 0.0);
	}

	if (!o->isColliding) {
		o->isColliding = true;
		o->hitbox.setColor(0.0, 1.0, 0.0);
	}
}

/* Get the 4 axes of a bounding box for the SAT */
void Object::getAxesSAT(float axes[4][2], BoundingBox *hitbox) {
	for (int i = 0; i < 4; i++) {
		/* Get 2 points that makes one edge of the box */
		Position p1 = hitbox->points[i];
		Position p2 = hitbox->points[i + 1 == 4 ? 0 : i + 1];

		/* Calculate the vector representing one edge of the box */
		float vec[2] = { p1.x - p2.x, p1.z - p2.z };

		/* Normalize the vector */
		float magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
		vec[0] = vec[0] / magnitude;
		vec[1] = vec[1] / magnitude;

		/* Store the axis as the normal of the vector */
		axes[i][0] = -vec[1];
		axes[i][1] = vec[0];
	}
}

/* Projection for the SAT */
void Object::projectObjectSAT(float axis[2], BoundingBox *hitbox, float projection[2]) {
	/* Initialize values */
	projection[0] = axis[0] * hitbox->points[0].x + axis[1] * hitbox->points[0].z;
	projection[1] = projection[0];
	
	/* Get the min and the max by looping through all points */
	for (int j = 1; j < 4; j++) {
		float p = axis[0] * hitbox->points[j].x + axis[1] * hitbox->points[j].z;

		if (p < projection[0]) {
			projection[0] = p;
		}
		else if (p > projection[1]) {
			projection[1] = p;
		}
	}
}
