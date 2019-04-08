/*
	Racing game project - Spectator class
	Represents a spectator (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____SPECTATOR____
#define ____SPECTATOR____

class Spectator {

private:
	float xPos;
	float yPos;
	float zPos;
	float currYPos;
	float color[3];
	bool jumping;
	bool goingUp;

	float bodyPos;
	float headPos;

public:

	/* Constructors */
	Spectator(float xPos, float yPos, float zPos, float color[3], bool jumping);
	Spectator(float xPos, float yPos, float zPos, float red, float green, float blue, bool jumping);
	Spectator(Spectator *s1);
	Spectator(void);

	/* Destructor */
	~Spectator(void);

	/* OpenGL code to draw the tree */
	void draw(void);

	/* Move a spectator*/
	void move(void);

	/* Print */
	void print(void);

	/* Getters */
	float getXPos(void);
	float getYPos(void);
	float getZPos(void);
	bool getJumping(void);
	float getCurrYPos(void);
	
	/* Setters */
	void setJumping(void);
};

#endif // Spectator