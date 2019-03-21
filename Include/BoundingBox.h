/*
	Racing game project - Hitbox_rect class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <Position.h>

class BoundingBox {
public:
	float length, width, height;
	Position points[8];	// The 8 points of the hitbox

public:
	/* Constructor */
	BoundingBox(float objLength, float objWidth, float objHeight, Position *objCenter);

	BoundingBox(BoundingBox *b);

	BoundingBox(void);

	/* Destructor */
	~BoundingBox(void);

	/* Update hitbox's points with a new position */
	void update(Position *newPos);

	/* Draw the hitbox */
	void draw(void);
};

#endif