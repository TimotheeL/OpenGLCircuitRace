/*
	Racing game project - BRT class
	Modelize the Besançon Racing Track (fictive)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#ifndef ____BRT____
#define ____BRT____

#include <vector>

#include "Billboard.h"
#include "Bleachers.h"
#include "Checker.h"
#include "Patch.h"
#include "StraightLine.h"
#include "Turn.h"

using namespace std;

class BRT {

protected:
	Checker checker;
	vector<Patch> patches;
	vector<TrackPart*> track;
	vector<Bleachers> bleachers;
	vector<Tree> trees;
	vector<Spectator> spectators;
	vector<Billboard> billboards;
	vector<unsigned int> texturesID;

public:
	/* Constructors */
	BRT(void);

	/* getters */
	Checker getChecker(void);
	vector<TrackPart*>* getTrack(void);
	vector<Patch> getPatches(void);
	vector<Tree> getTrees(void);
	vector<Bleachers> getBleachers(void);
	vector<Spectator> getSpectators(void);
	vector<Billboard> getBillboards(void);
	vector<unsigned int> getTexturesID(void);

	/* Update */
	void update(void);

	/* Draw */
	void draw(void);
	void drawBoundingBoxes(void);

	/* Collision */
	void resetIsColliding(void);

	/* Delete textures */
	void deleteTextures(void);
};

#endif // BRT