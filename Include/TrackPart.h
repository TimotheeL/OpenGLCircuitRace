/*
	Racing game project - TrackPart class
	Represents a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____TRACKPART____
#define ____TRACKPART____

#include <vector>

#include <Position.h>
#include <Object.h>

using namespace std;

class TrackPart : public Object {

protected:
	float width;
	Position pos;

	vector<Position> vertices;
	vector<Object> sideboxes;

	Position rotate(float x, float y, float z);

	/* Compute vertices */
	virtual void computeVertices(void);

	/* Basic bounding boxes generator for a track part */
	virtual void generateBoundingBoxes(void);

public:
	/* Constructors */
	TrackPart(void);
	TrackPart(float width, Position pos);
	TrackPart(TrackPart *p1);

	/* Destructor */
	~TrackPart(void);

	/* Getters */
	virtual float getWidth(void);
	virtual Position getPosition(void);
	vector<Position> getVertices(void);
	vector<Object> *getSideboxes(void);

	/* Setters */
	virtual void setWidth(float width);

	/* Drawer */
	virtual void draw(void);

	virtual void drawBoundingBoxes(void);

	/* Basic IsColliding resetter for a track part */
	virtual void resetIsColliding(void);
};

#endif // TrackPart