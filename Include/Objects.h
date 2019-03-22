/*
	Racing game project - Objects class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef OBJECTS_H
#define OBJECTS_H

#include <BoundingBox.h>

class Objects {
protected:
	BoundingBox hitbox;
	Position pos;

public:
	/* Constructors */
	Objects::Objects(float length, float width, float height, float x, float y, float z);

	Objects(BoundingBox b, Position pos);

	Objects(Objects *o);

	Objects(void);

	/* Destructor */
	virtual ~Objects(void);

	/* Getters */
	BoundingBox getBoundingBox(void);
	Position getPos(void);

	/* Draw */
	virtual void draw();
};

#endif