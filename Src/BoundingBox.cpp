/*
	Racing game project - BoundingBox class

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

const GLfloat rouge[] = { 1.0, 0.0, 0.0 };
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
	length = objLength;		// Set length to object length
	width = objWidth;		// Set width to object width
	height = objHeight;		// Set height to object height
	update(objCenter);		// Update the position of the box with the object position
}

BoundingBox::BoundingBox(BoundingBox *b) {
	length = b->length;
	width = b->width;
	height = b->height;
	
	for (int i = 0; i < 8; i++) {
		points[i] = new Position(b->points[i]);
	}
}

BoundingBox::BoundingBox(void)
	:BoundingBox(5.0, 5.0, 5.0, new Position())
{}

/* Destructor */
BoundingBox::~BoundingBox(void) {}

/* Update hitbox's points with a new position */
void BoundingBox::update(Position *newPos) {
	// TODO: probleme quand width > length

	// Calculate the radius of the box
	float radius = sqrt(width*width + length * length) / 2;
	// Calculate alpha, an angle of the rect triangle in the box
	float alpha = atan2(width, length);
	// Convert in rad
	float radangle = newPos->angle * PI / 180;

	float ar = radangle + alpha; // Rotation angle for points +x +z (0,4)
	float br = radangle - alpha;	// Rotation angle for points +x -z (1,5)
	float dr = br + PI;			// Rotation angle for points -x -z (2,6)
	float cr = ar - PI;			// Rotation angle for points -x +z (3,7)

	// Update each points
	points[0] = new Position(
		newPos->x + radius * cos(ar),
		newPos->y,
		newPos->z + radius * sin(ar),
		ar * 180 / PI
	);

	points[1] = new Position(
		newPos->x + radius * cos(br),
		newPos->y,
		newPos->z + radius * sin(br),
		br * 180 / PI
	);

	points[2] = new Position(
		newPos->x + radius * cos(cr),
		newPos->y,
		newPos->z + radius * sin(cr),
		cr * 180 / PI
	);

	points[3] = new Position(
		newPos->x + radius * cos(dr),
		newPos->y,
		newPos->z + radius * sin(dr),
		dr * 180 / PI
	);

	points[4] = new Position(
		newPos->x + radius * cos(ar),
		newPos->y + height,
		newPos->z + radius * sin(ar),
		ar * 180 / PI
	);

	points[5] = new Position(
		newPos->x + radius * cos(br),
		newPos->y + height,
		newPos->z + radius * sin(br),
		br * 180 / PI
	);

	points[6] = new Position(
		newPos->x + radius * cos(cr),
		newPos->y + height,
		newPos->z + radius * sin(cr),
		cr * 180 / PI
	);

	points[7] = new Position(
		newPos->x + radius * cos(dr),
		newPos->y + height,
		newPos->z + radius * sin(dr),
		dr * 180 / PI
	);
}

/* Draw the hitbox */
void BoundingBox::draw(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rouge);

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