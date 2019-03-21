/*
	Racing game project - Turn class
	Represents a turn as a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____TURN____
#define ____TURN____

#include "TrackPart.h"

class Turn : public TrackPart {

protected:
	float softness;
	float angle;
	char direction;

public:
	/* Constructors */
	Turn(void);
	Turn(float width, float softness, float angle, char direction);
	Turn(Turn *p1);

	/* Destructor */
	~Turn(void);

	/* Getters */
	float getSoftness(void);
	float getAngle(void);
	char getDirection(void);

	/* Setters */
	void setSoftness(float softness);
	void setAngle(float angle);
	void setDirection(char direction);

	/* Drawer */
	void draw(void);
};

#endif // Turn
