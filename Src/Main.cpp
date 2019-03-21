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

#include "StraightLine.h"

/* Global variables */
static int pMode = 1; 

static int wTx = 600;
static int wTy = 360;
static int wPx = 50;
static int wPy = 50;

/* Init function */
static void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

/* Test functions */
static void testNicolas(void) {
	StraightLine myLine = new StraightLine(7.0, 10.0); 
	myLine.build();
}

/* Scene function */
static void scene(void) {
	glPushMatrix();
	glPushMatrix();
	testNicolas();
	glPopMatrix();
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
	gluLookAt(0.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
		gluPerspective(60.0, ratio, 0.2, 100.0);
	else
		gluPerspective(60.0 / ratio, ratio, 0.2, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Idle function */
static void idle(void) {
	glutPostRedisplay();
}

/* Keyboard function */
static void keyboard(unsigned char key, int x, int y) {
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
		}
}

/* Special function*/
static void special(int specialKey, int x, int y) {
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
