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

	bool isColliding;

	float length;
	float width;
	float height;

public:
	/* Constructors */
	Object(float length, float width, float height, float x, float y, float z);

	Object(float length, float width, float height);

	Object(Object *o);

	Object(void);

	/* Destructor */
	virtual ~Object(void);

	/* Getters */
	BoundingBox getBoundingBox(void);
	Position getPos(void);
	float getLength(void);
	float getWidth(void);
	float getHeight(void);
	bool getIsColliding(void);

	/* Setters */
	void resetIsColliding(void);

	/* Draw */
	virtual void draw();

	/* Collision test between this object and another object
	 * using the Separating Axis Theorem (SAT)
	 * Y VALUES AREN'T TESTED
	 * Implemented thanks to : http://www.dyn4j.org/2010/01/sat/
	 */
	virtual void collisionTestSAT(Object *o);

private:
	/* Get the 4 axes of a bounding box for the SAT */
	void getAxesSAT(float axes1[4][2], BoundingBox *hitbox);

	/* Get the projections for the SAT */
	void projectObjectSAT(float axis[2], BoundingBox *hitbox, float minMax[2]);
};

#endif