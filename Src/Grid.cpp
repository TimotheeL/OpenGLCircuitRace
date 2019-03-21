/*
	Racing game project - Grid class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Grid.h>

/* Constructor */
Grid::Grid(void) { }

/* Destructor */
Grid::~Grid(void) { }

/* Draw */
void Grid::draw(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
	glBegin(GL_QUADS);

	int xsize = 0, ysize = 0;

	for (int i = 0; i < 20; i++) {
		xsize = 0;
		for (int j = 0; j < 20; j++) {
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-40.0 + xsize, 0.0, -40.0 + ysize);
			glVertex3f(-30.0 + xsize, 0.0, -40.0 + ysize);
			glVertex3f(-30.0 + xsize, 0.0, -30.0 + ysize);
			glVertex3f(-40.0 + xsize, 0.0, -30.0 + ysize);
			xsize += 10.0;
		}
		ysize += 10.0;
		
	}
	glEnd();
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}