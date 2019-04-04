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

public:

	/* Constructors */
	Tree(float xPos, float zPos, float wTrunk, float hTrunk, float wLeaves, float hLeaves);
	Tree(Tree *t1);

	/* Destructor */
	~Tree(void);

	/* OpenGL code to draw the tree */
	void draw(void);

	/* Print */
	void print(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getWTrunk(void);
	float getHTrunk(void);
	float getWLeaves(void);
	float getHLeaves(void);
};

#endif // Tree