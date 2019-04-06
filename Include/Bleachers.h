/*
	Racing game project - Bleachers class
	Represents bleachers with spectators (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/
#include <vector>
#include "Crowd.h"

#ifndef ____BLEACHERS____
#define ____BLEACHERS____

class Bleachers : public Crowd {

private:
	float xPos;
	float yPos;
	float zPos;
	float angle;
	float filling; // Between 0 and 1: determines how crowded the bleachers are
	int width;
	int depth;

public:

	/* Constructors */
	Bleachers(float xPos, float zPos, int width, int depth, float angle, float filling);
	Bleachers(Bleachers *b1);
	Bleachers(void);

	/* Destructor */
	~Bleachers(void);

	/* OpenGL code to draw the bleachers */
	void draw(void);

	/* Print */
	void print(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getAngle(void);
	float getFilling(void);
	int getWidth(void);
	int getDepth(void);
	std::vector<Spectator> getSpectators(void);

};

#endif // BLEACHERS
