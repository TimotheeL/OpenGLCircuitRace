/*
	Racing game project - BoundingBox class

	Represents a bounding box, characterized by 8 3D-points

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

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

const GLfloat blanc[] = { 1.0, 1.0, 1.0 };

/*	BoundingBox points structure

	bottom   top
	2-----1  6-----5
	|     |  |     |
	|  +  |  |  +  |	+ x
	|     |  |     |	z 
	3-----0  7-----4
*/

/* Constructors */
BoundingBox::BoundingBox(float objLength, float objWidth, float objHeight, Position *objCenter) {
	length = objLength;
	width = objWidth;
	height = objHeight;

	// Allocate memory for each point
	for (int i = 0; i < 8; i++) {
		points[i] = new Position();
	}

	update(objCenter);

	color[0] = 1.0; color[1] = 0.0; color[2] = 0.0;
}

BoundingBox::BoundingBox(BoundingBox *b) {
	length = b->length;
	width = b->width;
	height = b->height;

	color[0] = 1.0; color[1] = 0.0; color[2] = 0.0;

	for (int i = 0; i < 8; i++) {
		points[i] = new Position(b->points[i]);
	}
}

BoundingBox::BoundingBox(void)
	:BoundingBox(5.0, 5.0, 5.0, new Position())
{}

/* Destructor */
BoundingBox::~BoundingBox(void) {}

/* Setters */
void BoundingBox::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

/* Update hitbox's points with a new position */
void BoundingBox::update(Position *newPos) {
	// Calculate the radius of the box
	float radius = sqrtf(width * width + length * length) / 2;
	// Calculate alpha, an angle of the rect triangle in the box
	float alpha = atan2(width, length);
	// Convert in rad
	float radangle = newPos->angle * M_PI / 180;

	float ar = radangle + alpha;	// Rotation angle for points +x +z (0,4)
	float br = radangle - alpha;	// Rotation angle for points +x -z (1,5)
	float dr = br + M_PI;			// Rotation angle for points -x -z (2,6)
	float cr = ar - M_PI;			// Rotation angle for points -x +z (3,7)
	float pi180 = 180 / M_PI;

	// Update each points
	points[0].x = newPos->x + radius * cos(ar);
	points[0].y = newPos->y;
	points[0].z = newPos->z + radius * sin(ar);
	points[0].angle = ar * pi180;

	points[1].x = newPos->x + radius * cos(br);
	points[1].y = newPos->y;
	points[1].z = newPos->z + radius * sin(br);
	points[1].angle = br * pi180;

	points[2].x = newPos->x + radius * cos(cr);
	points[2].y = newPos->y;
	points[2].z = newPos->z + radius * sin(cr);
	points[2].angle = cr * pi180;

	points[3].x = newPos->x + radius * cos(dr);
	points[3].y = newPos->y;
	points[3].z = newPos->z + radius * sin(dr);
	points[3].angle = dr * pi180;

	points[4].x = newPos->x + radius * cos(ar);
	points[4].y = newPos->y + height;
	points[4].z = newPos->z + radius * sin(ar);
	points[4].angle = ar * pi180;

	points[5].x = newPos->x + radius * cos(br);
	points[5].y = newPos->y + height;
	points[5].z = newPos->z + radius * sin(br);
	points[5].angle = br * pi180;

	points[6].x = newPos->x + radius * cos(cr);
	points[6].y = newPos->y + height;
	points[6].z = newPos->z + radius * sin(cr);
	points[6].angle = cr * pi180;

	points[7].x = newPos->x + radius * cos(dr);
	points[7].y = newPos->y + height;
	points[7].z = newPos->z + radius * sin(dr);
	points[7].angle = dr * pi180;
}

/* Draw the hitbox */
void BoundingBox::draw(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

	glPushMatrix();
		glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
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
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blanc);
}