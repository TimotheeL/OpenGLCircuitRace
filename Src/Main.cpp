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

#include "Patch.h"
#include "Turn.h"
#include "StraightLine.h"
#include "Tree.h"

using namespace std;

/* Global variables */
static int pMode = 1; 

Patch patch = new Patch(-16.0, 16.0, 32.0, 5);

static int wTx = 600;
static int wTy = 360;
static int wPx = 50;
static int wPy = 50;

std::vector<StraightLine> lines;
std::vector<Turn> turns;

/* Besançon Racing Track modelizing function */
static void BRT(void) {
	
}

/* Init function */
static void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	BRT();
}

/* Scene function */
static void scene(void) {
	glPushMatrix();
	glPushMatrix();
	//patch.draw();
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].draw();
	}
	for (unsigned int i = 0; i < turns.size(); i++) {
		turns[i].draw();
	}
	/* glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 20; i++) {
		float rp = (float)i / 20;
		float ar = 2.0*3.1415926535897932384626433832795 / (360.0 / 90.0);
		float a = ar*rp;
		float cs = cos(a);
		float sn = -sin(a);
		float x = 7.0 * cs;
		float z = 7.0 * sn;

		float xin = 7.0 * cs - 7.0 - 7.0 / 2;
		float zin = 7.0 * sn;
		float xout = ((7.0 + 7.0) * cs - 7.0 - 7.0 / 2);
		float zout = (7.0 + 7.0) * sn;
		glVertex3f(xin, 0.0, zin);
		glVertex3f(xout, 0.0, zout);
	}
	glEnd(); */
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
	gluLookAt(0.0, 200.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
		gluPerspective(60.0, ratio, 0.2, 400.0);
	else
		gluPerspective(60.0 / ratio, ratio, 0.2, 400.0);
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
