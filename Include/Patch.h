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

using namespace std;

class Patch : public Crowd {

private:
	//Position of bottom left corner
	float xPos;
	float zPos;

	// Attributes to avoid calculations in the draw method
	float xPos2;
	float zPos2;

	// Size of the patch (width and height)
	float width;
	float height;

	int nbTrees;
	
	vector<Tree> trees;

	bool drawGrass;

	unsigned int textureID;

public:

	/* Constructors */
	Patch(float xPos, float zPos, float width, float height, int nbTrees, int nbSpectators, bool drawGrass, unsigned int texID);

	Patch(Patch *p1);

	Patch(void);

	/* Destructor */
	~Patch(void);

	/* Draw */
	void draw(void);

	/* Getters */
	float getXPos(void);
	float getZPos(void);
	float getWidth(void);
	float getHeight(void);
	int getNbTrees(void);
	bool getDrawGrass(void);
};

#endif // Patch