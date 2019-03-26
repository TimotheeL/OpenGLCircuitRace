/*
	Racing game project - Objects class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <BoundingBox.h>

class Object {
protected:
	BoundingBox hitbox;
	Position pos;

public:
	/* Constructors */
	Object(float length, float width, float height, float x, float y, float z);

	Object(float length, float width, float height);

	Object(BoundingBox b, Position pos);

	Object(Object *o);

	Object(void);

	/* Destructor */
	virtual ~Object(void);

	/* Getters */
	BoundingBox getBoundingBox(void);
	Position getPos(void);

	/* Draw */
	virtual void draw();

	/* Collision test between this object and another object */
	virtual void collisionTest(Object *o);
};

#endif