/* 
	Racing game project - Main program
	
	2019
	Nicolas Bouchard, Timothée Guy, Timothée Laurent
*/

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Global variables */
static int pMode = 1; 


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
	glutSolidTorus(0.2, 0.5, 72, 180);
	glPopMatrix();
}

/* Display function */
static void display(void) {
	printf("D\n");
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == 1) ? GL_FILL : GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}

/* Reshape function */
static void reshape(int wx, int wy) {
	printf("R\n");
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = (double)wx / wy;
	if (wx > wy)
		glOrtho(-ratio, ratio, -1.0, 1.0, -1.0, 1.0);
	else
		glOrtho(-1.0, 1.0, -1.0 / ratio, 1.0 / ratio, -1.0, 1.0);
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
	glutInitWindowSize(400.0, 400.0);
	glutInitWindowPosition(100.0, 100.0);
	glutCreateWindow("Gestion événementielle de GLUt");
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	//glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	//glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
