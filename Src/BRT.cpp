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

#include "PNG\ChargePngFile.h"

// Regular constructor
BRT::BRT(void) {
	// Texture loading
	unsigned int textureID;

	// Load grass texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int rx, ry;
	unsigned char* img = chargeImagePng("grass.png", &rx, &ry);

	if (img && textureID) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		free(img);
	}
	else {
		if (img) {
			free(img);
		}
		if (textureID) {
			glDeleteTextures(1, &textureID);
			textureID = 0;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	texturesID.push_back(textureID);

	track.push_back(new StraightLine(7.0f, 200.0f, new Position(100.0f, 0.0f, 80.0f, 90.0f)));
	track.push_back(new Turn(7.0f, 13.0f, 192.0f, false, new Position(-100.0f, 0.0f, 80.0f, 90.0f)));
	track.push_back(new StraightLine(7.0f, 22.0f, new Position(-96.8f, 0.0f, 47.3f, 258.0f)));
	track.push_back(new Turn(7.0f, 6.0f, 170.0f, true, new Position(-75.5f, 0.0f, 51.8f, 258.0f)));
	track.push_back(new StraightLine(7.0f, 42.0f, new Position(-69.9f, 0.0f, 33.7f, 68.0f)));
	track.push_back(new Turn(7.0f, 10.0f, 115.0f, false, new Position(-106.5f, 0.0f, 19.0f, 68.0f)));
	track.push_back(new StraightLine(7.0f, 20.0f, new Position(-111.0f, 0.0f, -3.0f, 313.0f)));
	track.push_back(new Turn(7.0f, 5.0f, 90.0f, false, new Position(-97.0f, 0.0f, -16.0f, 313.0f)));
	track.push_back(new StraightLine(7.0f, 45.0f, new Position(-85.1f, 0.0f, -15.7f, 223.0f)));
	track.push_back(new Turn(7.0f, 40.0f, 25.0f, false, new Position(-54.5f, 0.0f, 17.2f, 223.0f)));
	track.push_back(new Turn(7.0f, 20.0f, 72.0f, true, new Position(-45.0f, 0.0f, 33.2f, 198.0f)));
	track.push_back(new StraightLine(7.0f, 42.0f, new Position(-23.0f, 0.0f, 49.5f, 270.0f)));
	track.push_back(new Turn(7.0f, 8.0f, 180.0f, true, new Position(19.0f, 0.0f, 49.5f, 270.0f)));
	track.push_back(new StraightLine(7.0f, 28.0f, new Position(19.0f, 0.0f, 26.5f, 90.0f)));
	track.push_back(new Turn(7.0f, 2.0f, 47.0f, false, new Position(-9.0f, 0.0f, 26.5f, 90.0f)));
	track.push_back(new StraightLine(7.0f, 100.0f, new Position(-13.0f, 0.0f, 24.8f, 43.0f)));
	track.push_back(new Turn(7.0f, 10.3f, 80.0f, true, new Position(-81.1f, 0.0f, -48.3f, 43.0f)));
	track.push_back(new StraightLine(7.0f, 30.0f, new Position(-98.4f, 0.0f, -50.7f, 123.0f)));
	track.push_back(new Turn(7.0f, 5.0f, 90.0f, false, new Position(-123.5f, 0.0f, -34.5f, 123.0f)));
	track.push_back(new Turn(7.0f, 10.0f, 90.0f, false, new Position(-135.3f, 0.0f, -36.8f, 33.0f)));
	track.push_back(new StraightLine(7.0f, 43.5f, new Position(-132.3f, 0.0f, -54.7f, 303.0f)));
	track.push_back(new Turn(7.0f, 20.0f, 80.0f, false, new Position(-97.3f, 0.0f, -77.3f, 303.0f)));
	track.push_back(new StraightLine(7.0f, 90.0f, new Position(-67.4f, 0.0f, -73.7f, 223.0f)));
	track.push_back(new Turn(7.0f, 40.0f, 47.0f, true, new Position(-6.1f, 0.0f, -8.0f, 223.0f)));
	track.push_back(new StraightLine(7.0f, 12.0f, new Position(25.7f, 0.0f, 5.9f, 270.0f)));
	track.push_back(new Turn(7.0f, 22.0f, 70.0f, false, new Position(37.7f, 0.0f, 5.9f, 270.0f)));
	track.push_back(new StraightLine(7.0f, 30.0f, new Position(61.6f, 0.0f, 22.5f, 200.0f)));
	track.push_back(new Turn(7.0f, 5.0f, 90.0f, true, new Position(71.8f, 0.0f, 50.7f, 200.0f)));
	track.push_back(new StraightLine(7.0f, 9.7f, new Position(82.7f, 0.0f, 55.8f, 290.0f)));
	track.push_back(new Turn(7.0f, 12.3f, 90.0f, false, new Position(91.8f, 0.0f, 52.6f, 290.0f)));
	track.push_back(new Turn(7.0f, 9.9f, 110.0f, false, new Position(112.0f, 0.0f, 62.0f, 200.0f)));

	
	for (int i = -11; i < 9; i++) {
		for (int j = -6; j < 9; j++) {
			int nbTrees = 0;
			if (i < -10 || i > 7 || j < -5 || j > 7) {
				nbTrees = rand() % 5 + 3;
				patches.push_back(new Patch(i * 16.0f, j * 16.0f, 16.0f, 16.0f, nbTrees, 0, false, texturesID.at(0)));
			}
		}
	}

	checker = new Checker();
	bleachers.push_back(new Bleachers(-80.0f, 100.0f, 50, 10, 180.0f, 0.1f));
	bleachers.push_back(new Bleachers(-20.0f, 100.0f, 50, 10, 180.0f, 0.1f));
	bleachers.push_back(new Bleachers(40.0f, 100.0f, 50, 10, 180.0f, 0.1f));
	bleachers.push_back(new Bleachers(-50.0f, -43.0f, 50, 10, -47.0f, 0.1f));

	patches.push_back(new Patch(0.0, -16.0, 16.0, 16.0, 0, 5, false, texturesID.at(0)));
	patches.push_back(new Patch(16.0, 0.0, 16.0, 16.0, 0, 5, false, texturesID.at(0)));
	patches.push_back(new Patch(-88.0, -85.0, 8.0, 8.0, 0, 3, false, texturesID.at(0)));
	patches.push_back(new Patch(-72.0, -82.0, 8.0, 8.0, 0, 3, false, texturesID.at(0)));
	patches.push_back(new Patch(112.0, 96, 16.0, 16.0, 0, 5, false, texturesID.at(0)));
	patches.push_back(new Patch(100.0, 96, 8.0, 8.0, 0, 3, false, texturesID.at(0)));
	patches.push_back(new Patch(64.0, 16.0, 16.0, 16.0, 0, 6, false, texturesID.at(0)));
	patches.push_back(new Patch(48.0, 0.0, 16.0, 16.0, 0, 3, false, texturesID.at(0)));
	patches.push_back(new Patch(80.0, 44.0, 12.0, 12.0, 0, 4, false, texturesID.at(0)));
	patches.push_back(new Patch(118.0, 54.0, 6.0, 6.0, 0, 3, false, texturesID.at(0)));
	patches.push_back(new Patch(-128.0, -80.0, 16.0, 16.0, 0, 4, false, texturesID.at(0)));
	patches.push_back(new Patch(-144.0, -64.0, 16.0, 16.0, 0, 5, false, texturesID.at(0)));
	patches.push_back(new Patch(-160.0, -32.0, 16.0, 16.0, 0, 4, false, texturesID.at(0)));
	for (int i = -16; i < 96; i += 16) {
		patches.push_back(new Patch(-144.0, (float)i, 16.0, 16.0, 0, rand() % 5, false, texturesID.at(0)));
	}
	for (int i = -80; i < 100; i += 20) {
		trees.push_back(new Tree((float)i, 70.0, 0.5, 3.0, 2.0, 4.0));
	}
	for (int i = -80; i < 100; i += 3) {
		billboards.push_back(new Billboard((float)i, 0.0f, 74.0f, 3.0f, 0.5f, 0.0f, 0.6f));
		billboards.push_back(new Billboard((float)i, 0.0f, 74.0f, 3.0f, 0.5f, 0.0f, 0.0f));
		billboards.push_back(new Billboard((float)i, 0.0f, 86.0f, 3.0f, 0.5f, 180.0f, 0.6f));
		billboards.push_back(new Billboard((float)i, 0.0f, 86.0f, 3.0f, 0.5f, 180.0f, 0.0f));
	}

	billboards.push_back(new Billboard(-120.0, 0.0, 90.0, 6.0, 3.5, 135.0, 1.5));
	patches.push_back(new Patch(-176, 128, 320, 240.0, 0, 0, true, texturesID.at(0)));
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

vector<unsigned int> BRT::getTexturesID(void) {
	return texturesID;
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

void BRT::deleteTextures(void)
{
	for (unsigned int i = 0; i < texturesID.size(); i++) {
		glDeleteTextures(1, &texturesID.at(i));
	}
}
