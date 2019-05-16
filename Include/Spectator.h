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
	float bodyPos;
	float headPos;

	bool jumping;
	bool goingUp;

public:

	/* Constructors */
	Spectator(float xPos, float yPos, float zPos, float color[3], bool jumping);

	Spectator(float xPos, float yPos, float zPos, float red, float green, float blue, bool jumping);

	Spectator(Spectator *s1);

	Spectator(void);

	/* Destructor */
	~Spectator(void);

	/* Draw */
	void draw(void);

	/* Move a spectator*/
	void move(void);

	/* Getters */
	float getXPos(void);
	float getYPos(void);
	float getZPos(void);
	bool getJumping(void);
	float getCurrYPos(void);
	
	/* Setter */
	void setJumping(void);
};

#endif // Spectator