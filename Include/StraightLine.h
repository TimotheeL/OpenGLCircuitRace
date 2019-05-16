/*
	Racing game project - StraightLine class
	Represents a straight line as a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____STRAIGHTLINE____
#define ____STRAIGHTLINE____

#include "Position.h"
#include "TrackPart.h"

class StraightLine : public TrackPart {

protected:
	float length;

	/* Compute vertices */
	virtual void computeVertices(void);

	/* Bounding boxes generator */
	virtual void generateBoundingBoxes(float offset);

public:
	/* Constructors */
	StraightLine(void);

	StraightLine(float width, float length, Position pos);

	StraightLine(StraightLine *p1);

	/* Destructor */
	~StraightLine(void);

	/* Getters */
	float getLength(void);

	/* Setters */
	void setLength(float length);

	/* Draw */
	void draw(void);
};

#endif // StraightLine
