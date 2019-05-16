/*
	Racing game project - Tree class
	Represents a tree (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____TREE____
#define ____TREE____

class Tree {

private:
	float xPos;
	float zPos;
	float wTrunk;
	float hTrunk;
	float wLeaves;
	float hLeaves;

	// Attributes used to pre compute the centers, in order to avoid calculations in the draw method
	float centerLeaves;
	float centerTrunk;

public:

	/* Constructors */
	Tree(float xPos, float zPos, float wTrunk, float hTrunk, float wLeaves, float hLeaves);

	Tree(Tree *t1);

	Tree(void);

	/* Destructor */
	~Tree(void);

	/* Draw */
	void draw(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getWTrunk(void);
	float getHTrunk(void);
	float getWLeaves(void);
	float getHLeaves(void);
};

#endif // Tree