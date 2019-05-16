/*
	Racing game project - Checker class
	Represents a checker pattern (Used for the start line)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____CHECKER____
#define ____CHECKER____

class Checker {

private:
	float xPos;
	float zPos;
	float squareSize;

	int width;
	int height;

public:
	/* Constructors */
	Checker(float xPos, float zPos, float squareSize, int width, int height);

	Checker(Checker *c1);

	Checker(void);

	/* Destructor */
	~Checker(void);

	/* Draw */
	void draw(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getSize(void);
	int getWidth(void);
	int getHeight(void);
};

#endif // Checker