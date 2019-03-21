/*
	Racing game project - Main program

	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <RacingCar.h>
#include <Grid.h>
#include <Position.h>

/* Global variables */
static int pMode = 1;

const double dt = 1 / 60.0;	/* Framerate */
double currentTime = 0.0;	/* Current time */
double accumulator = 0.0;	/* Time accumulator */

/* Boolean arrays of keyboard keys states */
bool keyStates[256];
bool keySpecialStates[256];

/* Racing Cars */
RacingCar *rc;
RacingCar *rc2;

/* A grid */
Grid *grid;

/* Init function */
static void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	rc = new RacingCar(4.0, 2.0, 2.0);
	rc2 = new RacingCar(4.0, 2.0, 2.0, 10.0, 0.0, -10.0); // This one doesn't move
	grid = new Grid();
}

/* Scene function */
static void scene(void) {
	glPushMatrix();

		/* Draw the camera locked on the racing car */
		Position rcpos = rc->getPos();
		gluLookAt(
			0.0 + rcpos.x, 8.0 + rcpos.y, 10.0 + rcpos.z,
			rcpos.x, rcpos.y, rcpos.z,
			0.0, 1.0, 0.0
		);

		/* Draw objects */
		rc->draw();
		rc2->draw();
		grid->draw();

		/* Draw bounding boxes */
		rc->getBoundingBox().draw();
		rc2->getBoundingBox().draw();

	glPopMatrix();
}

/* Input handling and physic simulation function */
static void simulate(void) {
	/* Handle inputs for the car */
	rc->handleInputs(keyStates, keySpecialStates);
	/* Handle car's movement */
	rc->handleMovement(dt);
}

/* Display function */
static void display(void) {
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == 1) ? GL_FILL : GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Get time and calculate frame time in seconds */
	double newTime = glutGet(GLUT_ELAPSED_TIME);
	double frameTime = (newTime - currentTime) / 1000;
	currentTime = newTime;

	/* Synchronize simulation framerate and real framerate :
			- accumulate frametime
			- if the accumulator is superior than the wanted framerate
			do the sim and substract the framerate
	*/
	accumulator += frameTime;
	while (accumulator >= dt)
	{
		simulate();
		accumulator -= dt;
	}

	/* Draw scene */
	scene();

	glFlush();
	glutSwapBuffers();

	int error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Attention erreur %d\n", error);
	}
}

/* Reshape function */
static void reshape(int wx, int wy) {
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double ratio = (double)wx / wy;

	if (ratio > 1.0) {
		gluPerspective(60.0F, ratio, 0.1, 100.0);
	}
	else {
		gluPerspective(60.0F / ratio, ratio, 0.1, 100.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Idle function */
static void idle(void) {
	glutPostRedisplay();
}

/* Key pressed function */
static void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = true;

	switch (key) {
		case 'p':
		case 'P':
			pMode = !pMode;
			glutPostRedisplay();
			break;
		case 'f':
		case 'F':
			glutFullScreen();
			break;
		case 0x1B:
			exit(0);
			break;
	}
}

/* Key released function */
static void keyboardUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

/* Special key pressed function*/
static void special(int specialKey, int x, int y) {
	keySpecialStates[specialKey] = true;
}

/* Special key released function */
static void specialUp(int specialKey, int x, int y) {
	keySpecialStates[specialKey] = false;
}

/* Mouse function */
static void mouseButton(int buton, int state, int x, int y) {
}

/* Mouse function with pressed button */
static void mouseMotion(int x, int y) {
}

/* Mouse function without pressed button */
static void passiveMouseMotion(int x, int y) {
}

/* Called on exit */
static void clean(void) {
}

/* Main */
int main(int argc, char **argv) {

	atexit(clean);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800.0, 600.0);
	glutInitWindowPosition(100.0, 100.0);
	glutCreateWindow("DEJA VU");
	init();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
