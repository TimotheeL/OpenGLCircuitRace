/*
	Racing game project - Object class

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

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

/*-- Classes written to be synctactically comprehensive --*/

/* MTV : Constructor */
MTV::MTV(void) {
	overlap = FLT_MAX;
	axis = Axis();
}

/* MTV : Destructor */
MTV::~MTV(void) {}

/*------------------------------
	Object Class
--------------------------------*/

/* Constructors */
Object::Object(float length, float width, float height, Position *posi) {
	pos = new Position(posi);
	hitbox = new BoundingBox(length, width, height, &pos);
	this->length = length;
	this->width = width;
	this->height = height;
	isColliding = false;
	movingForward = true;
}

Object::Object(float length, float width, float height)
	:Object(length, width, height, new Position(0.0, 0.0, 0.0))
{}

Object::Object(Object *o)
{
	pos = new Position(o->getPos());
	hitbox = new BoundingBox(o->getBoundingBox());
	length = o->length;
	width = o->width;
	height = o->height;
	isColliding = o->isColliding;
	movingForward = o->movingForward;
}

Object::Object(void)
	:Object(5.0, 5.0, 5.0, new Position(0.0, 0.0, 0.0))
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

bool Object::getMovingForward(void) {
	return movingForward;
}

/* Setters */
void Object::resetIsColliding(void) {
	isColliding = false;
}

/* Draw */
void Object::draw(void) {
	hitbox.draw();
}

void Object::drawBoundingBoxes(void) {
	hitbox.draw();
}

/* Collision handling */
void Object::collision(Object *o) {
	MTV *mtv = collisionTestSAT(o);

	if (mtv != NULL) {
		if (movingForward) {
			pos.x += mtv->axis.x * mtv->overlap;
			pos.z += mtv->axis.z * mtv->overlap;
		}
		else {
			pos.x -= mtv->axis.x * mtv->overlap;
			pos.z -= mtv->axis.z * mtv->overlap;
		}

		hitbox.update(&pos);
	}
}

/* Collision test between this object and another object
 * using the Separating Axis Theorem (SAT)
 * Y VALUES AREN'T TESTED
 * Implemented thanks to : http://www.dyn4j.org/2010/01/sat/
 */
MTV *Object::collisionTestSAT(Object *o) {
	/* An axis is a normal of a side of the object 
	 * We don't use the Y parameter of our bounding boxes,
	 * so we'll check only 4 axes like in a 2D world
	 * An axis is a 2D normalized vector
	 */
	Axis axes[4];  // Axes for this object
	Axis oaxes[4]; // Axes for the other object

	/* A projection is composed of [0] = min and [1] = max.
	 * Thoses are the result of the projection of the points of a bounding box
	 * on one of the axis previously found
	 */
	Projection *projection = new Projection();
	Projection *oprojection = new Projection();

	/* MTV : the Minimum Translation Vector is used to reposition the object
	 * if there's a collision
	 */
	MTV *mtv = new MTV();
	float overlap = 0.0;

	/* Get the axes */
	getAxesSAT(axes, &hitbox);
	getAxesSAT(oaxes, &o->hitbox);

	/* For every axis found for the first object */
	for (int i = 0; i < 4; i++) {
		/* Do the projection for both objects */
		projectObjectSAT(axes[i], &hitbox, projection);
		projectObjectSAT(axes[i], &o->hitbox, oprojection);

		overlap = getOverlap(projection, oprojection);

		/* Check projections overlapping */
		if (overlap == 0.0) {
			/* If there's no overlap, there's no collision, return nothing
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}

			/* Free memory */
			delete(projection);
			delete(oprojection);
			delete(mtv);

			return NULL;
		}
		else if (overlap < mtv->overlap) {
			mtv->overlap = overlap;
			mtv->axis = axes[i];
		}
	}

	/* For every axis found for the second object */
	for (int i = 0; i < 4; i++) {
		/* Do the projection for both objects */
		projectObjectSAT(oaxes[i], &hitbox, projection);
		projectObjectSAT(oaxes[i], &o->hitbox, oprojection);

		/* Calculate overlap */
		overlap = getOverlap(projection, oprojection);

		/* Check projections overlapping */
		if (overlap == 0) {
			/* If there's no overlap, there's no collision, return nothing
			 * Change the color if there's no collision at all
			 */
			if (!isColliding) {
				hitbox.setColor(1.0, 0.0, 0.0);
			}

			if (!o->isColliding) {
				o->hitbox.setColor(1.0, 0.0, 0.0);
			}

			/* Free memory */
			delete(projection);
			delete(oprojection);
			delete(mtv);
			
			return NULL;
		}
		else if (overlap < mtv->overlap) {
			mtv->overlap = overlap;
			mtv->axis = axes[i];
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

	/* Free memory */
	delete(projection);
	delete(oprojection);

	/* If the mtv and the dir of the object points in 
	 * the same direction, reverse the mtv
	 */
	float radangle = pos.angle * M_PI / 180;
	float p = cos(radangle) * mtv->axis.x + sin(radangle) * mtv->axis.z;
	if (p >= 0.0) {
		mtv->axis.x = -mtv->axis.x;
		mtv->axis.z = -mtv->axis.z;
	}

	/* Return the MTV */
	return mtv;
}

/* Get the overlap between two projections */
float Object::getOverlap(Projection *projection, Projection *oprojection) {
	return max(0, min(projection->max, oprojection->max) - max(projection->min, oprojection->min));
}

/* Get the 4 axes of a bounding box for the SAT */
void Object::getAxesSAT(Axis axes[4], BoundingBox *hitbox) {
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
		axes[i].x = -vec[1];
		axes[i].z = vec[0];
	}
}

/* Projection for the SAT */
void Object::projectObjectSAT(Axis axis, BoundingBox *hitbox, Projection *projection) {
	/* Initialize values */
	projection->min = axis.x * hitbox->points[0].x + axis.z * hitbox->points[0].z;
	projection->max = projection->min;
	
	/* Get the min and the max by looping through all points */
	for (int j = 1; j < 4; j++) {
		/* Dot product */
		float p = axis.x * hitbox->points[j].x + axis.z * hitbox->points[j].z;

		if (p < projection->min) {
			projection->min = p;
		}
		else if (p > projection->max) {
			projection->max = p;
		}
	}
}
