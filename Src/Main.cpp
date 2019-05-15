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

#include "BRT.h"
#include "RacingCar.h"
#include "Billboard.h"

using namespace std;

/* Global variables */
static bool wiremode = false; 
static bool drawBBox = false;
static bool fullscreen = false;
static int switchGameMode = 0;

const double dt = 1 / 60.0;	/* Simulation framerate */
double currentTime = 0.0;	/* Current time */
double accumulator = 0.0;	/* Time accumulator */

/* Boolean arrays of keyboard keys states */
bool keyStates[256];
bool keySpecialStates[256];

static int wTx = 800;
static int wTy = 600;
static int wPx = 50;
static int wPy = 50;

static float eye_x = 0.0; // 0.0
static float eye_y = 180.0; // 180.0
static float eye_z = 1.0; // 1.0

/* Player's racing car */
RacingCar rc;

/* Racing track */
BRT brt;

/* Init function */
static void init(void) {
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glClearColor(0.1F, 0.4F, 0.9F, 1.0F);

	/* Init circuit */
	brt = BRT();
	/* Init player's racing Car */
	rc = RacingCar(4.0, 1.5, 1.8, new Position(85.0, 0.0, 80.0, 180.0));
}

/* Scene function */
static void scene(void) {
	glPushMatrix();

		/* Draw */
		brt.draw();
		rc.draw();

		/* Draw bounding boxes */
		if (drawBBox) {
			rc.drawBoundingBoxes();
			brt.drawBoundingBoxes();
		}
	glPopMatrix();
}

/* Input handling and physic simulation function */
static void simulate(void) {
	brt.update();

	if (switchGameMode == 1) {
		/* Reset colliding states */
		rc.resetIsColliding();
		brt.resetIsColliding();

		/* Handle inputs for the car */
		rc.handleInputs(keyStates, keySpecialStates);
		/* Handle car's movement */
		rc.handleMovement(dt);

		/* Handle collisions */
		rc.collision(&brt);
	}
}

const float ambient[] = { 0.75F, 0.75F, 0.65F, 1.0F };
const float ambient2[] = { 0.5F, 0.5F, 0.4F, 1.0F };
const float ambient3[] = { 0.25F, 0.25F, 0.25F, 1.0F };

const GLfloat posa[] = { 0.0, 100.0, 150.0, 1.0 };
const GLfloat posb[] = { 150.0, 100.0, 0.0, 1.0 };
const GLfloat posc[] = { -150.0, 100.0, 0.0, 1.0 };
const GLfloat posd[] = { 0.0, 100.0, -150.0, 1.0 };

/* Display function */
static void display(void) {
	if (!wiremode) {
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

	glPushMatrix();
		switch (switchGameMode) {
			case 0: rc.setCamera(true); break;
			case 1: rc.setCamera(false); break;
			default: gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		}

		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_POSITION, posa);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, ambient2);
		glLightfv(GL_LIGHT1, GL_POSITION, posb);

		glLightfv(GL_LIGHT2, GL_DIFFUSE, ambient2);
		glLightfv(GL_LIGHT2, GL_POSITION, posc);

		glLightfv(GL_LIGHT3, GL_DIFFUSE, ambient3);
		glLightfv(GL_LIGHT3, GL_POSITION, posd);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);

		scene();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

/* Reshape function */
static void reshape(int wx, int wy) {
	wTx = wx;
	wTy = wy;
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double ratio = (double)wx / wy;
	ratio > 1.0 ? gluPerspective(60.0, ratio, 0.2, 1000.0) : gluPerspective(60.0 / ratio, ratio, 0.2, 1000.0);

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
		case 't':
			wiremode = !wiremode;
			glutPostRedisplay();
			break;
		case 'f':
		case 'F':
			fullscreen = !fullscreen;

			if (fullscreen) {
				glutReshapeWindow(wTx, wTy);
				glutPositionWindow(wPx, wPy);
			}
			else {
				glutFullScreen();
			}
			break;
		case 0x1B:
			exit(0);
			break;
		case 'p':
		case 'P':
			eye_y += 2.0;
			break;
		case 'm':
		case 'M':
			eye_y -= 2.0;
			break;
		case 'b':
		case 'B':
			drawBBox = !drawBBox;
			glutPostRedisplay();
			break;
		case 13:
			switchGameMode++;
			if (switchGameMode > 2) {
				switchGameMode = 0;
			}
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

	if (switchGameMode == 2) {
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
	glutCreateWindow("Besancon Racing Track");
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
