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

#include "Checker.h"
#include "Patch.h"
#include "StraightLine.h"
#include "Turn.h"
#include "Tree.h"

using namespace std;

/* Global variables */
static int pMode = 1; 

static int wTx = 800;
static int wTy = 600;
static int wPx = 50;
static int wPy = 50;

static float eye_x = 0.0; // 0.0
static float eye_y = 180.0; // 180.0
static float eye_z = 1.0; // 1.0

std::vector<Patch> patches;
Checker checker = new Checker(80.0, 83.0, 0.5, 4, 14);
std::vector<StraightLine> lines;
std::vector<Turn> turns;

/* Besançon Racing Track modelizing function */
static void BRT(void) {
	for (int i = -16; i < 16; i++) {
		for (int j = -16; j < 16; j++) {
			int nbTrees = 0;
			//nbTrees = abs(i * j) / 16 + abs(i + j) / 4; // comment this line to remove all trees
			patches.push_back(new Patch(i * 16.0, j * 16.0, 16.0, nbTrees));
		}
	}
	lines.push_back(new StraightLine(7.0, 200.0, new Position(100.0, 0.0, 80.0, 90.0)));
	turns.push_back(new Turn(7.0, 13.0, 192.0, false, new Position(-100.0, 0.0, 80.0, 90.0)));
	lines.push_back(new StraightLine(7.0, 22.0, new Position(-96.8, 0.0, 47.3, 258.0)));
	turns.push_back(new Turn(7.0, 6.0, 170.0, true, new Position(-75.5, 0.0, 51.8, 258.0)));
	lines.push_back(new StraightLine(7.0, 42.0, new Position(-69.9 , 0.0, 33.7, 68.0)));
	turns.push_back(new Turn(7.0, 10.0, 115.0, false, new Position(-106.5, 0.0, 19.0, 68.0)));
	lines.push_back(new StraightLine(7.0, 20.0, new Position(-111.0, 0.0, -3.0, 313.0)));
	turns.push_back(new Turn(7.0, 5.0, 90.0, false, new Position(-97.0, 0.0, -16.0, 313.0)));
	lines.push_back(new StraightLine(7.0, 45.0, new Position(-85.1, 0.0, -15.7, 223.0)));
	turns.push_back(new Turn(7.0, 40.0, 25.0, false, new Position(-54.5, 0.0, 17.2, 223.0)));
	turns.push_back(new Turn(7.0, 20.0, 72.0, true, new Position(-45.0, 0.0, 33.2, 198.0)));
	lines.push_back(new StraightLine(7.0, 42.0, new Position(-23.0, 0.0, 49.5, 270.0)));
	turns.push_back(new Turn(7.0, 8.0, 180.0, true, new Position(19.0, 0.0, 49.5, 270.0)));
	lines.push_back(new StraightLine(7.0, 28.0, new Position(19.0, 0.0, 26.5, 90.0)));
	turns.push_back(new Turn(7.0, 2.0, 47.0, false, new Position(-9.0, 0.0, 26.5, 90.0)));
}

/* Init function */
static void init(void) {
	glClearColor(0.1F, 0.4F, 0.9F, 1.0F);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	BRT();
}

/* Scene function */
static void scene(void) {
	checker.draw();
	glPushMatrix();
		glPushMatrix();
			for (unsigned int i = 0; i < patches.size(); i++) {
				patches[i].draw();
			}
		glPopMatrix();
		glPushMatrix();
			for (unsigned int i = 0; i < turns.size(); i++) {
				turns[i].draw();
			}
			for (unsigned int i = 0; i < lines.size(); i++) {
				lines[i].draw();
			}
		glPopMatrix();
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
	gluLookAt(eye_x, eye_y, eye_z, 80.0, 0.0, 90.0, 0.0, 1.0, 0.0);
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
		case 'p':
			eye_y += 10.0;
			break;
		case 'm':
			eye_y -= 10.0;
			break;
	}
}

/* Special function*/
static void special(int specialKey, int x, int y) {
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
