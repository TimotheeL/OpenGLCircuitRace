/*
	Racing game project - BoundingBox class

	Represents a bounding box, characterized by 8 3D-points

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef ____BOUNDINGBOX____
#define ____BOUNDINGBOX____

#include <GL/gl.h>

#include <Position.h>

class BoundingBox {
public:
	float length, width, height;
	Position points[8];
	GLfloat color[3];

	/*	BoundingBox points structure

		bottom   top
		2-----1  6-----5
		|     |  |     |
		|  +  |  |  +  |	+ x
		|     |  |     |	z
		3-----0  7-----4
	*/

public:
	/* Constructors */
	BoundingBox(float objLength, float objWidth, float objHeight, Position *objCenter);

	BoundingBox(BoundingBox *b);

	BoundingBox(void);

	/* Destructor */
	~BoundingBox(void);

	/* Setter */
	void setColor(float r, float g, float b);

	/* Update hitbox's points with a new position */
	void update(Position *newPos);

	/* Draw the hitbox */
	void draw(void);
};

#endif