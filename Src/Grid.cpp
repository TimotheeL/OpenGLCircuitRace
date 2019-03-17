/*
	Racing game project - Grid class

	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
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

	int xsize = 0, ysize = 0;

	for (int i = 0; i < 10; i++) {
		xsize = 0;
		for (int j = 0; j < 10; j++) {
			glBegin(GL_POLYGON);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-20.0 + xsize, 0.0, -20.0 + ysize);
			glVertex3f(-10.0 + xsize, 0.0, -20.0 + ysize);
			glVertex3f(-10.0 + xsize, 0.0, -10.0 + ysize);
			glVertex3f(-20.0 + xsize, 0.0, -10.0 + ysize);
			glEnd();
			xsize += 10.0;
		}
		ysize += 10.0;
		
	}

	glPopMatrix();
}