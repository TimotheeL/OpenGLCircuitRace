/*
	Racing game project - Position class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef POSITION_H
#define POSITION_H

class Position {

public:
	float x, y, z;

public:
	/* Constructors */
	Position(void);

	Position(float x, float y, float z);

	Position(Position *p);

	/* Destructor */
	~Position(void);
};

#endif