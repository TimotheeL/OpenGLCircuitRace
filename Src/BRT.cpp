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
	lines.push_back(new StraightLine(7.0, 200.0, new Position(100.0, 0.0, 80.0, 90.0)));
	turns.push_back(new Turn(7.0, 13.0, 192.0, false, new Position(-100.0, 0.0, 80.0, 90.0)));
	lines.push_back(new StraightLine(7.0, 22.0, new Position(-96.8, 0.0, 47.3, 258.0)));
	turns.push_back(new Turn(7.0, 6.0, 170.0, true, new Position(-75.5, 0.0, 51.8, 258.0)));
	lines.push_back(new StraightLine(7.0, 42.0, new Position(-69.9, 0.0, 33.7, 68.0)));
	turns.push_back(new Turn(7.0, 10.0, 115.0, false, new Position(-106.5, 0.0, 19.0, 68.0)));
	lines.push_back(new StraightLine(7.0, 20.0, new Position(-111.0, 0.0, -3.0, 313.0)));
	turns.push_back(new Turn(7.0, 5.0, 90.0, false, new Position(-97.0, 0.0, -16.0, 313.0)));
	lines.push_back(new StraightLine(7.0, 45.0, new Position(-85.1, 0.0, -15.7, 223.0)));
	turns.push_back(new Turn(7.0, 40.0, 25.0, false, new Position(-54.5, 0.0, 17.2, 223.0)));
	turns.push_back(new Turn(7.0, 20.0, 72.0, true, new Position(-45.0, 0.0, 33.2, 198.0)));
	lines.push_back(new StraightLine(7.0, 42.0, new Position(-23.0, 0.0, 49.5, 270.0)));
	turns.push_back(new Turn(7.0, 8.0, 180.0, true, new Position(19.0, 0.0, 49.5, 270.0)));
	lines.push_back(new StraightLine(7.0, 28.0, new Position(19.0, 0.0, 26.5, 90.0)));
	turns.push_back(new Turn(7.0, 2.0, 47.0, false, new Position(-9.0, 0.0, 26.5, 90.0)));
	lines.push_back(new StraightLine(7.0, 100.0, new Position(-13.0, 0.0, 24.8, 43.0)));
	turns.push_back(new Turn(7.0, 10.0, 80.0, true, new Position(-81.1, 0.0, -48.4, 43.0)));

	for (int i = -16; i < 16; i++) {
		for (int j = -16; j < 16; j++) {
			int nbTrees = 0;
			if (i < -11 || i > 8 || j < -11 || j > 8)
				nbTrees = abs(i * j) / 32 + abs(i + j) / 4;
			patches.push_back(new Patch(i * 16.0, j * 16.0, 16.0, nbTrees));
		}
	}

	checker = new Checker();

	bleachers.push_back(new Bleachers(-20.0, 100.0, 50, 10, 180.0, 0.5));
	bleachers.push_back(new Bleachers(40.0, 100.0, 50, 10, 180.0, 0.5));
}

// getters
vector<StraightLine> BRT::getLines(void) {
	return lines;
}
vector<Turn> BRT::getTurns(void) {
	return turns;
}

// Update
void BRT::update(void) {
	for (unsigned int i = 0; i < bleachers.size(); i++) {
		bleachers[i].update();
	}
}

// drawer
void BRT::draw(void) {
	checker.draw();
	for (unsigned int i = 0; i < patches.size(); i++) {
		patches[i].draw();
	}
	for (unsigned int i = 0; i < turns.size(); i++) {
		turns[i].draw();
	}
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].draw();
	}
	for (unsigned int i = 0; i < bleachers.size(); i++) {
		bleachers[i].draw();
	}
}

void BRT::drawBoundingBoxes(void) {
	for (unsigned int i = 0; i < turns.size(); i++) {
		turns[i].drawBoundingBoxes();
	}
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].drawBoundingBoxes();
	}
}