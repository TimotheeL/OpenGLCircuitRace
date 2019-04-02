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

private:
	float radians(float angle);

protected:
	float width;
	Position pos;
	std::vector<Position> vertices;
	Position rotate(float x, float y, float z);

public:
	/* Constructors */
	TrackPart(void);
	TrackPart(float width, Position pos);
	TrackPart(TrackPart *p1);

	/* Destructor */
	~TrackPart(void);

	/* Getters */
	float virtual getWidth(void);
	Position virtual getPosition(void);
	std::vector<Position> getVertices(void);

	/* Setters */
	void virtual setWidth(float width);

	/* Drawer */
	void virtual draw(void);
};

#endif // TrackPart