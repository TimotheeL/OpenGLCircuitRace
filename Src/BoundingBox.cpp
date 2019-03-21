/*
	Racing game project - Hitbox_rect class

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <BoundingBox.h>

#define PI 3.14159265

/* Constructor */
BoundingBox::BoundingBox(float objLength, float objWidth, float objHeight, Position *objCenter) {
	length = objLength;
	width = objWidth;
	height = objHeight;

	update(objCenter);
}

BoundingBox::BoundingBox(BoundingBox *b) {
	length = b->length;
	width = b->width;
	height = b->height;
	
	for (int i = 0; i < 8; i++) {
		points[i] = new Position(b->points[i]);
	}
}

/* Destructor */
BoundingBox::~BoundingBox(void) { }

/* Update hitbox's points with a new position */
void BoundingBox::update(Position *newPos) {
	float radius = sqrt(width*width + length * length) / 2;
	float alpha = atan2(width, length);

	float radangle = newPos->angle * PI / 180;

	float a = radangle + alpha;
	float b = radangle - alpha;
	float c = b + 180;
	float d = a - 180;

	points[0] = new Position(
		newPos->x + radius * cos(a),
		newPos->y,
		newPos->z + radius * sin(a),
		a
	);

	points[1] = new Position(
		newPos->x + radius * cos(b),
		newPos->y,
		newPos->z + radius * sin(b),
		b
	);

	points[2] = new Position(
		newPos->x + radius * cos(c),
		newPos->y,
		newPos->z + radius * sin(c),
		c
	);

	points[3] = new Position(
		newPos->x + radius * cos(d),
		newPos->y,
		newPos->z + radius * sin(d),
		d
	);

	points[4] = new Position(
		newPos->x + radius * cos(a),
		newPos->y + height,
		newPos->z + radius * sin(a),
		a
	);

	points[5] = new Position(
		newPos->x + radius * cos(b),
		newPos->y + height,
		newPos->z + radius * sin(b),
		b
	);

	points[6] = new Position(
		newPos->x + radius * cos(b + 180),
		newPos->y + height,
		newPos->z + radius * sin(b + 180),
		b + 180
	);

	points[7] = new Position(
		newPos->x + radius * cos(a - 180),
		newPos->y + height,
		newPos->z + radius * sin(a - 180),
		a - 180
	);
}

/* Draw the hitbox */
void BoundingBox::draw(void) {
	const GLfloat rouge[] = { 1.0, 0.0, 0.0 };

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rouge);

	glPushMatrix();
		glBegin(GL_QUADS);	
			// 0 1 2 3
			for (int i = 0; i < 4; i++) {
				glVertex3f(points[i].x, points[i].y, points[i].z);
			}

			// 4 5 6 7
			for (int i = 4; i < 8; i++) {
				glVertex3f(points[i].x, points[i].y, points[i].z);
			}

			// 0 1 5 4
			glVertex3f(points[0].x, points[0].y, points[0].z);
			glVertex3f(points[1].x, points[1].y, points[1].z);
			glVertex3f(points[5].x, points[5].y, points[5].z);
			glVertex3f(points[4].x, points[4].y, points[4].z);
			
			// 3 2 6 7
			glVertex3f(points[3].x, points[3].y, points[3].z);
			glVertex3f(points[2].x, points[2].y, points[2].z);
			glVertex3f(points[6].x, points[6].y, points[6].z);
			glVertex3f(points[7].x, points[7].y, points[7].z);
			
			// 0 3 7 4
			glVertex3f(points[0].x, points[0].y, points[0].z);
			glVertex3f(points[3].x, points[3].y, points[3].z);
			glVertex3f(points[7].x, points[7].y, points[7].z);
			glVertex3f(points[4].x, points[4].y, points[4].z);
			
			// 1 2 6 5
			glVertex3f(points[1].x, points[1].y, points[1].z);
			glVertex3f(points[2].x, points[2].y, points[2].z);
			glVertex3f(points[6].x, points[6].y, points[6].z);
			glVertex3f(points[5].x, points[5].y, points[5].z);
		glEnd();
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}