/*
	Racing game project - Racing car class

	Represents a racing car, with all its properties

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <RacingCar.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

const float RacingCar::MAX_SPD_FW = 10.0;
const float RacingCar::MAX_SPD_BW = 5.0;
const float RacingCar::ACCEL = 3.0;
const float RacingCar::ROT_ANGLE = 2.0;

/* Constructors */
RacingCar::RacingCar(float clength, float cwidth, float cheight, Position *pos)
	:Object(clength, cwidth, cheight, pos)
{
	handbrakeState = false;
	movingForward = true;
	speed = 0.0;
}

RacingCar::RacingCar(float clength, float cwidth, float cheight)
	:RacingCar(clength, cwidth, cheight, new Position(0.0, 0.0, 0.0))
{}

RacingCar::RacingCar(void)
	:RacingCar(0.0, 0.0, 0.0)
{}

RacingCar::RacingCar(RacingCar *rc)
	:Object(rc)
{
	speed = rc->getSpeed();
	handbrakeState = rc->getHandbrakeState();
	movingForward = rc->getMovingForward();
}

/* Destructor */
RacingCar::~RacingCar(void) {}

/* Getters */
float RacingCar::getSpeed(void) {
	return speed;
}

bool RacingCar::getHandbrakeState(void) {
	return handbrakeState;
}

/* Draw */
void RacingCar::draw(void) {
	const GLfloat blanc[] = { 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blanc);

	glPushMatrix();
		glTranslatef(pos.x, pos.y + height/4, pos.z);
		glRotatef(pos.angle, 0.0, -1.0, 0.0);

		glPushMatrix();
			glScalef(length, height/2, width);
			glutSolidCube(1.0);
		glPopMatrix();
	
		glPushMatrix();
			glScalef(length*0.5, height/2, width);
			glTranslatef(-0.2, height/2, 0.0);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

/* Input handling */
void RacingCar::handleInputs(bool *keyStates, bool *specialKeyStates) {

	/* Reset the car when r, R */
	if (keyStates['r'] || keyStates['R']) {
		reset();
	}

	/* If the handbrake is on, the car can't move */
	/* NOTE: on my laptop, if key_up + key_left or key_down + key_right
	the handbrake doesn't work, certainly due to keyboard itslef */
	if (keyStates[' ']) {
		handbrake();
	}
	else {
		// Move forward when KEY_UP, z, Z
		if (specialKeyStates[GLUT_KEY_UP] || keyStates['z'] || keyStates['Z']) {
			forward(ACCEL);
		}

		// Move backward when KEY_DOWN, s, S
		if (specialKeyStates[GLUT_KEY_DOWN] || keyStates['s'] || keyStates['S']) {
			backward(ACCEL);
		}

		// Rotate to the right when KEY_RIGHT, d, D
		if (specialKeyStates[GLUT_KEY_RIGHT] || keyStates['d'] || keyStates['D']) {
			turnRight(ROT_ANGLE);
		}

		// Rotate to the right when KEY_LEFT, q, Q
		if (specialKeyStates[GLUT_KEY_LEFT] || keyStates['q'] || keyStates['Q']) {
			turnLeft(ROT_ANGLE);
		}
	}
}

/* Movement handling */
void RacingCar::handleMovement(double deltaTime) {
	// If the speed isn't at zero
	if (speed != 0.0) {
		float radangle = pos.angle * M_PI / 180;

		// Calculate new position
		if (movingForward) {
			pos.x += speed * deltaTime * cos(radangle);
			pos.z += speed * deltaTime * sin(radangle);
		}
		else {
			pos.x -= speed * deltaTime * cos(radangle);
			pos.z -= speed * deltaTime * sin(radangle);
		}
		
		/* Slow the car over the time, if the handbrake is on, 
		slow the car 10 times faster */
		if (handbrakeState) {
			(speed > 0) ? speed -= 1.0 : speed = 0.0;
		}
		else {
			(speed > 0) ? speed -= 0.1 : speed = 0.0;
		}

		hitbox.update(&pos);
	}
}

void RacingCar::setCamera(void) {
	float radangle = (pos.angle + 90.0) * M_PI / 180;

	gluLookAt(
		pos.x + sin(-radangle) * 10.0,
		pos.y + 6.0,
		pos.z + cos(radangle) * 10.0,
		pos.x, pos.y, pos.z,
		0.0, 1.0, 0.0
	);
}

/* Forward */
void RacingCar::forward(float distance) {
	movingForward = true;
	handbrakeState = false;
	(speed < MAX_SPD_FW) ? speed += distance : speed = MAX_SPD_FW;
}

/* Backward */
void RacingCar::backward(float distance) {
	movingForward = false;
	handbrakeState = false;
	(speed < MAX_SPD_BW) ? speed += distance : speed = MAX_SPD_BW;
}

/* Turn right */
void RacingCar::turnRight(float degrees) {
	if (pos.angle >= 180) {
		pos.angle = -180 + (pos.angle - 180);
	}
	pos.angle += degrees;
	hitbox.update(&pos);
}

/* Turn left */
void RacingCar::turnLeft(float degrees) {
	if (pos.angle <= -180) {
		pos.angle = 180 - (pos.angle + 180);
	}
	pos.angle -= degrees;
	hitbox.update(&pos);
}

/* Use the handbrake */
void RacingCar::handbrake() {
	handbrakeState = true;
}

/* Reset car's properties */
void RacingCar::reset() {
	pos = new Position(0, 0, 0, -90);
	speed = 0.0;
	handbrakeState = false;
	movingForward = true;
	hitbox.update(&pos);
}

/* Collision handling */
void RacingCar::collision(Object *o) {
	MTV *mtv = collisionTestSAT(o);

	if (mtv != NULL) {
		if (movingForward) {
			pos.x += mtv->axis.x * mtv->overlap;
			pos.z += mtv->axis.z * mtv->overlap;
		}
		else {
			pos.x -= mtv->axis.x * mtv->overlap;
			pos.z -= mtv->axis.z * mtv->overlap;
		}

		speed = 0.0;
		hitbox.update(&pos);
	}

	delete(mtv);
}

void RacingCar::collision(TrackPart *tp) {
	vector<Object> *boxes = tp->getSideboxes();
	for (unsigned int i = 0; i < boxes->size(); i++) {
		MTV *mtv = collisionTestSAT(&boxes->at(i));

		// If there's a collision
		if (mtv != NULL) {
			// Adjust the position of the car
			if (movingForward) {
				pos.x += mtv->axis.x * mtv->overlap;
				pos.z += mtv->axis.z * mtv->overlap;
			}
			else {
				pos.x -= mtv->axis.x * mtv->overlap;
				pos.z -= mtv->axis.z * mtv->overlap;
			}

			// Adjust the angle
			if ((pos.angle > 0 && pos.angle < 90)
				|| (pos.angle > -180 && pos.angle < -90)) 
			{
				turnRight(1.0);
			}
			else if ((pos.angle > 90 && pos.angle < 180)
				|| (pos.angle > -90 && pos.angle < 0))
			{
				turnLeft(1.0);
			}

			// Adjust speed
			speed = 0.0;

			// Adjust hitbox
			hitbox.update(&pos);
		}

		delete(mtv);
	}
}

void RacingCar::collision(BRT *brt) {
	vector<TrackPart*> *track = brt->getTrack();

	for (unsigned int i = 0; i < track->size(); i++) {
		collision(track->at(i));
	}
}