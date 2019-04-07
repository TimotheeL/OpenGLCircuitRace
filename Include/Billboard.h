/*
	Racing game project - Billboard class
	Represents a billboard (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/
#include <vector>

#ifndef ____BILLBOARD____
#define ____BILLBOARD____

class Billboard {

private:
	float xPos;
	float yPos;
	float zPos;
	float width;
	float height;
	float angle;
	float feetHeight;

public:
	/* Constructors */
	Billboard(float xPos, float yPos, float zPos, float width, float height, float angle, float feetHeight);
	Billboard(Billboard *b1);
	Billboard(void);

	/* Destructor */
	~Billboard(void);

	/* OpenGL code to draw the bleachers */
	void draw(void);

	void update(void);

	/* Getters */
	float getXPos(void);
	float getYPos(void);
	float getZPos(void);
	float getAngle(void);
	float getWidth(void);
	float getHeight(void);
	float getFeetHeight(void);
};

#endif // BILLBOARD