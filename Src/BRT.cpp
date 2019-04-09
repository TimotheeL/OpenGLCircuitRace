/*
	Racing game project - BRT class
	Modelize the Besançon Racing Track (fictive)
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <vector>

#include "BRT.h"
#include "Checker.h"
#include "Patch.h"
#include "StraightLine.h"
#include "Turn.h"

// Regular constructor
BRT::BRT(void) {
	track.push_back(new StraightLine(7.0, 200.0, new Position(100.0, 0.0, 80.0, 90.0)));
	track.push_back(new Turn(7.0, 13.0, 192.0, false, new Position(-100.0, 0.0, 80.0, 90.0)));
	track.push_back(new StraightLine(7.0, 22.0, new Position(-96.8, 0.0, 47.3, 258.0)));
	track.push_back(new Turn(7.0, 6.0, 170.0, true, new Position(-75.5, 0.0, 51.8, 258.0)));
	track.push_back(new StraightLine(7.0, 42.0, new Position(-69.9, 0.0, 33.7, 68.0)));
	track.push_back(new Turn(7.0, 10.0, 115.0, false, new Position(-106.5, 0.0, 19.0, 68.0)));
	track.push_back(new StraightLine(7.0, 20.0, new Position(-111.0, 0.0, -3.0, 313.0)));
	track.push_back(new Turn(7.0, 5.0, 90.0, false, new Position(-97.0, 0.0, -16.0, 313.0)));
	track.push_back(new StraightLine(7.0, 45.0, new Position(-85.1, 0.0, -15.7, 223.0)));
	track.push_back(new Turn(7.0, 40.0, 25.0, false, new Position(-54.5, 0.0, 17.2, 223.0)));
	track.push_back(new Turn(7.0, 20.0, 72.0, true, new Position(-45.0, 0.0, 33.2, 198.0)));
	track.push_back(new StraightLine(7.0, 42.0, new Position(-23.0, 0.0, 49.5, 270.0)));
	track.push_back(new Turn(7.0, 8.0, 180.0, true, new Position(19.0, 0.0, 49.5, 270.0)));
	track.push_back(new StraightLine(7.0, 28.0, new Position(19.0, 0.0, 26.5, 90.0)));
	track.push_back(new Turn(7.0, 2.0, 47.0, false, new Position(-9.0, 0.0, 26.5, 90.0)));
	track.push_back(new StraightLine(7.0, 100.0, new Position(-13.0, 0.0, 24.8, 43.0)));
	track.push_back(new Turn(7.0, 10.3, 80.0, true, new Position(-81.1, 0.0, -48.3, 43.0)));
	track.push_back(new StraightLine(7.0, 30.0, new Position(-98.4, 0.0, -50.7, 123.0)));
	track.push_back(new Turn(7.0, 5.0, 90.0, false, new Position(-123.5, 0.0, -34.5, 123.0)));
	track.push_back(new Turn(7.0, 10.0, 90.0, false, new Position(-135.3, 0.0, -36.8, 33.0)));
	track.push_back(new StraightLine(7.0, 43.5, new Position(-132.3, 0.0, -54.7, 303.0)));
	track.push_back(new Turn(7.0, 20.0, 80.0, false, new Position(-97.3, 0.0, -77.3, 303.0)));
	track.push_back(new StraightLine(7.0, 90.0, new Position(-67.4, 0.0, -73.7, 223.0)));
	track.push_back(new Turn(7.0, 40.0, 47.0, true, new Position(-6.1, 0.0, -8.0, 223.0)));
	track.push_back(new StraightLine(7.0, 12.0, new Position(25.7, 0.0, 5.9, 270.0)));
	track.push_back(new Turn(7.0, 22.0, 70.0, false, new Position(37.7, 0.0, 5.9, 270.0)));
	track.push_back(new StraightLine(7.0, 30.0, new Position(61.6, 0.0, 22.5, 200.0)));
	track.push_back(new Turn(7.0, 5.0, 90.0, true, new Position(71.8, 0.0, 50.7, 200.0)));
	track.push_back(new StraightLine(7.0, 9.7, new Position(82.7, 0.0, 55.8, 290.0)));
	track.push_back(new Turn(7.0, 12.3, 90.0, false, new Position(91.8, 0.0, 52.6, 290.0)));
	track.push_back(new Turn(7.0, 9.9, 110.0, false, new Position(112.0, 0.0, 62.0, 200.0)));

	patches.push_back(new Patch(-176, 128, 320, 240.0, 0, 0, true));
	for (int i = -11; i < 9; i++) {
		for (int j = -6; j < 9; j++) {
			int nbTrees = 0;
			if (i < -10 || i > 7 || j < -5 || j > 7) {
				nbTrees = rand() % 5 + 3;
				patches.push_back(new Patch(i * 16.0, j * 16.0, 16.0, 16.0, nbTrees, 0, false));
			}
			/* TEMPORARY GRID OF SPECTATORS
			if (i == 0 && j == 0) {
				spectators.push_back(new Spectator(i * 16.0, 0.0, j * 16.0, 1.0, 1.0, 1.0, false));
			} else if (i % 2 == 0 && j % 2 == 0) {
				spectators.push_back(new Spectator(i * 16.0, 0.0, j * 16.0, 1.0, 0.0, 0.0, false));
			} else {
				spectators.push_back(new Spectator(i * 16.0, 0.0, j * 16.0, 0.0, 0.0, 1.0, false));
			}*/
		}
	}

	checker = new Checker();
	bleachers.push_back(new Bleachers(-80.0, 100.0, 50, 10, 180.0, 0.1));
	bleachers.push_back(new Bleachers(-20.0, 100.0, 50, 10, 180.0, 0.1));
	bleachers.push_back(new Bleachers(40.0, 100.0, 50, 10, 180.0, 0.1));
	bleachers.push_back(new Bleachers(-50.0, -43.0, 50, 10, -47.0, 0.1));

	patches.push_back(new Patch(0.0, -16.0, 16.0, 16.0, 0, 5, false));
	patches.push_back(new Patch(16.0, 0.0, 16.0, 16.0, 0, 5, false));
	patches.push_back(new Patch(-88.0, -85.0, 8.0, 8.0, 0, 3, false));
	patches.push_back(new Patch(-72.0, -82.0, 8.0, 8.0, 0, 3, false));
	patches.push_back(new Patch(112.0, 96, 16.0, 16.0, 0, 5, false));
	patches.push_back(new Patch(100.0, 96, 8.0, 8.0, 0, 3, false));
	patches.push_back(new Patch(64.0, 16.0, 16.0, 16.0, 0, 6, false));
	patches.push_back(new Patch(48.0, 0.0, 16.0, 16.0, 0, 3, false));
	patches.push_back(new Patch(80.0, 44.0, 12.0, 12.0, 0, 4, false));
	patches.push_back(new Patch(118.0, 54.0, 6.0, 6.0, 0, 3, false));
	patches.push_back(new Patch(-128.0, -80.0, 16.0, 16.0, 0, 4, false));
	patches.push_back(new Patch(-144.0, -64.0, 16.0, 16.0, 0, 5, false));
	patches.push_back(new Patch(-160.0, -32.0, 16.0, 16.0, 0, 4, false));
	for (int i = -16; i < 96; i += 16) {
		patches.push_back(new Patch(-144.0, (float)i, 16.0, 16.0, 0, rand() % 5, false));
	}
	for (int i = -80; i < 100; i += 20) {
		trees.push_back(new Tree((float)i, 70.0, 0.5, 3.0, 2.0, 4.0));
	}
	for (int i = -80; i < 100; i += 3) {
		billboards.push_back(new Billboard((float)i, 0.0, 74.0, 3.0, 0.5, 0.0, 0.6));
		billboards.push_back(new Billboard((float)i, 0.0, 74.0, 3.0, 0.5, 0.0, 0.0));
		billboards.push_back(new Billboard((float)i, 0.0, 86.0, 3.0, 0.5, 180.0, 0.6));
		billboards.push_back(new Billboard((float)i, 0.0, 86.0, 3.0, 0.5, 180.0, 0.0));
	}

	billboards.push_back(new Billboard(-120.0, 0.0, 90.0, 6.0, 3.5, 135.0, 1.5));
}

// getters
vector<TrackPart*> *BRT::getTrack(void) {
	return &track;
}

Checker BRT::getChecker(void) {
	return checker;
}

vector<Patch> BRT::getPatches(void) {
	return patches;
}

vector<Tree> BRT::getTrees(void) {
	return trees;
}

vector<Bleachers> BRT::getBleachers(void) {
	return bleachers;
}

vector<Spectator> BRT::getSpectators(void) {
	return spectators;
}
vector<Billboard> BRT::getBillboards(void) {
	return billboards;
}

// Update
void BRT::update(void) {
	for (unsigned int i = 0; i < bleachers.size(); i++) {
		bleachers[i].update();
	}
	for (unsigned int i = 0; i < spectators.size(); i++) {
		spectators[i].move();
	}
	for (unsigned int i = 0; i < patches.size(); i++) {
		patches[i].update();
	}
	/*for (unsigned int i = 0; i < billboards.size(); i++) {
		billboards[i].update();
	}*/
}

// drawer
void BRT::draw(void) {
	for (unsigned int i = 0; i < patches.size(); i++) {
		patches[i].draw();
	}

	for (unsigned int i = 0; i < bleachers.size(); i++) {
		bleachers[i].draw();
	}

	for (unsigned int i = 0; i < trees.size(); i++) {
		trees[i].draw();
	}

	for (unsigned int i = 0; i < spectators.size(); i++) {
		spectators[i].draw();
	}

	for (unsigned int i = 0; i < billboards.size(); i++) {
		billboards[i].draw();
	}

	checker.draw();
	for (unsigned int i = 0; i < track.size(); i++) {
		track[i]->draw();
	}
}

void BRT::drawBoundingBoxes(void) {
	for (unsigned int i = 0; i < track.size(); i++) {
		track[i]->drawBoundingBoxes();
	}
}

void BRT::resetIsColliding(void) {
	for (unsigned int i = 0; i < track.size(); i++) {
		track[i]->resetIsColliding();
	}
}