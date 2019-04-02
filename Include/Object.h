/*
	Racing game project - Object class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef ____OBJECT____
#define ____OBJECT____

#include <BoundingBox.h>

/*-- Classes written to be synctactically comprehensive --*/

/* Axis : a class representing an axis for the SAT */
class Axis {
public:
	float x;
	float z;
};

/* Projection : a projection of coordinates on an axis */
class Projection {
public:
	float min;
	float max;
};

/* MTV : a Minimum Translation Vector */
class MTV {
public:
	Axis axis;
	float overlap;
public:
	MTV(void);
	~MTV(void);
};

/*------------------------------
	Object Class
--------------------------------*/
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

	/* Collision handling */
	virtual void collision(Object *o);

	/* Collision test between this object and another object using the Separating Axis Theorem (SAT)
	 * Returns a Minimum Translation Vector
	 * Y VALUES AREN'T TESTED
	 * Implemented thanks to : http://www.dyn4j.org/2010/01/sat/
	 */
	MTV *collisionTestSAT(Object *o);

private:
	/* Get the 4 axes of a bounding box for the SAT */
	void getAxesSAT(Axis axes[4], BoundingBox *hitbox);

	/* Get the projections for the SAT */
	void projectObjectSAT(Axis axis, BoundingBox *hitbox, Projection *projection);

	/* Get the overlap between two projections */
	float getOverlap(Projection *projection, Projection *oprojection);
};

#endif