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

	/* OpenGL code to draw the checker pattern */
	void draw(void);

	/* Print */
	//void print(void);

	/* Getters */
	float Checker::getXPos(void);
	float Checker::getZPos(void);
	float Checker::getSize(void);
	int Checker::getWidth(void);
	int Checker::getHeight(void);
};

#endif // Checker