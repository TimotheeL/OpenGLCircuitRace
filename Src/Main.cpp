/* 
	Racing game project - Main program
	
	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdlib.h>
#include <stdio.h> 
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "Spectator.h"
#include "Bleachers.h"
#include "BRT.h"
#include "RacingCar.h"

using namespace std;

/* Global variables */
static int pMode = 1; 
static bool drawBBox = false;

const double dt = 1 / 60.0;	/* Framerate */
double currentTime = 0.0;	/* Current time */
double accumulator = 0.0;	/* Time accumulator */

/* Boolean arrays of keyboard keys states */
bool keyStates[256];
bool keySpecialStates[256];

static int wTx = 800;
static int wTy = 600;
static int wPx = 50;
static int wPy = 50;

Checker checker;
vector<Patch> patches;
vector<StraightLine> lines;
vector<Turn> turns;
Bleachers bleachers;

static float eye_x = 0.0; // 0.0
static float eye_y = 180.0; // 180.0
static float eye_z = 1.0; // 1.0


/* Player's racing car */
RacingCar rc;

/* Racing track */
BRT brt;

/* Init function */
static void init(void) {
	glClearColor(0.1F, 0.4F, 0.9F, 1.0F);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	/* Init circuit */
	brt = BRT();
	/* Init player's racing Car */
	rc = RacingCar(4.0, 2.0, 2.0, new Position(80.0, 0.0, 78.0));
}

/* Scene function */
static void scene(void) {
	glPushMatrix();


		
		gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		/* Draw */
		glPushMatrix();
			brt.draw();
			rc.draw();
			checker.draw();
			bleachers.draw();
		glPopMatrix();

		/* Draw bounding boxes */
		if (drawBBox) {
			rc.drawBoundingBoxes();
			brt.drawBoundingBoxes();
		}
	glPopMatrix();
}

/* Input handling and physic simulation function */
static void simulate(void) {
	/* Reset colliding states */
	//rc->resetIsColliding();
	/*for (unsigned int i = 0; i < brt.getLines().size(); i++) {
		brt.getLines()[i].resetIsColliding();
	}

	for (unsigned int i = 0; i < brt.getTurns().size(); i++) {
		brt.getTurns()[i].resetIsColliding();
	} */

	/* Handle inputs for the car */
	//rc->handleInputs(keyStates, keySpecialStates);
	/* Handle car's movement */
	//rc->handleMovement(dt);

	/* Handle collisions */
	/*for (unsigned int i = 0; i < listTrackParts.size(); i++) {
		rc->collision(listTrackParts[i]);
	}

	for (unsigned int i = 0; i < listObjects.size(); i++) {
		rc->collision(listObjects[i]);
	}*/
}

/* Display function */
static void display(void) {
	if (pMode == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_LIGHTING);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_LIGHTING);
	}

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
	wTx = wx;
	wTy = wy;
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double ratio = (double)wx / wy;

	if (ratio > 1.0)
		gluPerspective(60.0, ratio, 0.2, 1000.0);
	else
		gluPerspective(60.0 / ratio, ratio, 0.2, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Idle function */
static void idle(void) {
	glutPostRedisplay();
}

/* Keyboard function */
static void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = true;

	switch (key) {
		case ' ':
			{ pMode = !pMode;
			glutPostRedisplay(); }
		break;
		case 'f':
		case 'F':
			glutFullScreen();
			break;
		case 0x1B:
			exit(0);
			break;
		case 'p':
		case 'P':
			eye_y += 10.0;
			break;
		case 'm':
		case 'M':
			eye_y -= 10.0;
			break;
		case 'b':
		case 'B':
			drawBBox = !drawBBox;
			glutPostRedisplay();
			break;
	}
}

/* Key released function */
static void keyboardUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

/* Special function*/
static void special(int specialKey, int x, int y) {
	keySpecialStates[specialKey] = true;

	switch (specialKey) {
		case GLUT_KEY_UP:
			eye_z -= 2.0;
			break;
		case GLUT_KEY_DOWN:
			eye_z += 2.0;
			break;
		case GLUT_KEY_LEFT:
			eye_x -= 2.0;
			break;
		case GLUT_KEY_RIGHT:
			eye_x += 2.0;
	}
}

/* Special key released function */
static void specialUp(int specialKey, int x, int y) {
	keySpecialStates[specialKey] = false;
}

/* Mouse function */
static void mouse(int buton, int state, int x, int y) {
}

/* Mouse function with pressed button */
static void mouseMotion(int x, int y) {
}

/* Mouse function without pressed button */
static void passiveMouseMotion(int x, int y) {
}

/* Called on exit */
static void clean(void) {
	printf("Bye\n");
}

/* Main */
int main(int argc, char **argv) {

	atexit(clean);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(wTx, wTy);
	glutInitWindowPosition(wPx, wPy);
	glutCreateWindow("Circuit");
	init();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
