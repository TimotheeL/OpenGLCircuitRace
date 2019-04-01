/*
	Racing game project - Patch class
	Represents a patch of grass (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/
#include <vector>

#include <Tree.h>

#ifndef ____PATCH____
#define ____PATCH____

class Patch {

private:
	//Position of bottom left corner
	float xPos;
	float zPos;
	// Size of the patch (patches are squares)
	float size;
	int nbTrees;
	std::vector<Tree> trees;

public:

	/* Constructors */
	Patch(float xPos, float zPos, float size, int nbTrees);
	Patch(Patch *p1);

	/* Destructor */
	~Patch(void);

	/* OpenGL code to draw the patch */
	void draw(void);

	/* Print */
	//void print(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getSize(void);
	int getNbTrees(void);
};

#endif // Patch