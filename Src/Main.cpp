/* 
	Racing game project - Main program
	
	2019
	Nicolas Bouchard, Timothee Guy, Timothee Laurent
*/

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Tree.h"

/* Global variables */
static int pMode = 1; 

static int wTx = 600;
static int wTy = 360;
static int wPx = 50;
static int wPy = 50;

static double px = 0.0;
static double py = 6.0;
static double pz = 15.0;

static double angle = 0.0;
static float colorTrunk[4] = {0.5, 0.2, 0.18, 1.0};
static float colorLeaves[4] = {0.1, 0.5, 0.1, 1.0};


Tree test = new Tree(0.0, 0.0, 0.5, 1.5, 2.0, 4.0, 3.0, 5.0, 2.0, 6.0);

/* Init function */
static void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

/* Scene function */
static void scene(void) {
	glPushMatrix();
	test.build();
	glPopMatrix();
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
	glPushMatrix();
	gluLookAt(px, py, pz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	scene();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
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
		gluPerspective(80.0, ratio, 1.0, 20.0);
	else
		gluPerspective(80.0 / ratio, ratio, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Idle function */
static void idle(void) {
	angle += 2.0;
	glutPostRedisplay();
}

/* Keyboard function */
static void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case ' ':
			{ pMode = !pMode;
			glutPostRedisplay(); }
		break;
		case 's':
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

/* Special function*/
static void special(int specialKey, int x, int y) {
	switch (specialKey) {
		case GLUT_KEY_UP:
			py += 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			py -= 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			px -= 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			px += 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_UP:
			pz -= 0.1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_PAGE_DOWN:
			pz += 0.1;
			glutPostRedisplay();
			break;
	}
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
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
