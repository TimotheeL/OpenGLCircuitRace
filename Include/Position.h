/*
	Racing game project - Position class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#ifndef ____POSITION____
#define ____POSITION____

class Position {

public:
	float x, y, z, angle;

public:
	/* Constructors */
	Position(void);

	Position(float cx, float cy, float cz);

	Position(float cx, float cy, float cz, float cangle);

	Position(Position *p);

	/* Destructor */
	~Position(void);
};

#endif