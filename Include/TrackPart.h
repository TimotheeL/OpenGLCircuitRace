/*
	Racing game project - TrackPart class
	Represents a ciruit part
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____TRACKPART____
#define ____TRACKPART____

class TrackPart {

protected:
	float width;

public:
	/* Constructors */
	TrackPart(void);
	TrackPart(TrackPart *p1);

	/* Destructor */
	~TrackPart(void);

	/* Getters */
	float virtual getWidth(void);

	/* Setters */
	void virtual setWidth(float width);

	/* Builder */
	void virtual build(void);
};

#endif // TrackPart