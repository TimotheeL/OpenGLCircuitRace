/*
	Racing game project - Patch class
	Represents a patch of grass (background element)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/
#include <vector>

#include <Crowd.h>
#include <Tree.h>

#ifndef ____PATCH____
#define ____PATCH____

class Patch : public Crowd {

private:
	//Position of bottom left corner
	float xPos;
	float zPos;
	// Size of the patch (patches are squares)
	float size;
	int nbTrees;
	std::vector<Tree> trees;

	// Attributes to avoid calculations in the draw method
	float xPos2;
	float zPos2;

public:

	/* Constructors */
	Patch(float xPos, float zPos, float size, int nbTrees);
	Patch(float xPos, float zPos, float size, int nbTrees, int nbSpectators);
	Patch(Patch *p1);
	Patch(void);

	/* Destructor */
	~Patch(void);

	/* OpenGL code to draw the patch */
	void draw(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getSize(void);
	int getNbTrees(void);
};

#endif // Patch