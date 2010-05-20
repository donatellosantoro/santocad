// |        Generated by SantoCAD             |
// |  http://code.google.com/p/santocad/      |
// |  Michele Santomauro - Donatello Santoro  |
#include <windows.h>
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "FreeImage.h"
#include "cml/cml.h"
#include "materiali.h"
#include "textureUtil.h"
#include "scenaUtil.h"

using namespace cml;

GLint windowWidth, windowHeight;
// Gestione Camera
//${GESTIONE_CAMERA}
vector3f up(0.0, 1.0, 0.0);
vector3f side(1.0, 0.0, 0.0);
bool moveLeft, moveRight, 
	 moveForward, moveBackward, 
	 rotateLeft, rotateRight = false;
//${VARIABILI_TEXTURE}
//${VARIABILI_PLANE}
// Prototipi
void gestisciIlluminazione();
void disegnaPavimento(int tassellazione, bool wireframe);
void disegnaSkybox(GLint idTextureSkymap, int posizioneY);

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pos[0], pos[1], pos[2], 
			  at[0], at[1], at[2], 
			  up[0], up[1], up[2]);

	gestisciIlluminazione();

	//${DISEGNO_PAVIMENTO}
	//${DISEGNO_SKYBOX}
	//${DISEGNO_OGGETTI}

	glFlush(); 
	glutSwapBuffers();
}
//---------------GESTIONE MOVIMENTI------------------------------
void myIdle(){
	// Spostamento in avanti
	if(moveForward){
		pos = pos + dir;//${CONTROLLA_LIMITI}
		at = pos + dir;
	}
	// Spostamento all'indietro
	if(moveBackward){
		pos = pos - dir;//${CONTROLLA_LIMITI}
		at = pos + dir;
	}
	// Ruota a sinistra
	if(rotateLeft){
		dir = rotate_vector(dir, vector3f(0.0, 1.0, 0.0), -0.02);
		at = pos + dir;
		side = cross(dir, up);
		side.normalize();
	}
	// Ruota a destra
	if(rotateRight){
		dir = rotate_vector(dir, vector3f(0.0, 1.0, 0.0), 0.02);
		at = pos + dir;
		side = cross(dir, up);
		side.normalize();
	}
	// Spostamento laterale destro
	if(moveRight){
		pos = pos - 0.2*side;//${CONTROLLA_LIMITI}
		at = pos + dir;
	}
	// Spostamento laterale sinistro
	if(moveLeft){
		pos = pos + 0.2*side;//${CONTROLLA_LIMITI}
		at = pos + dir;
	}
	glutPostRedisplay();
}
void myKeyboardUp(unsigned char key, int x, int y){
	switch(key) {
		case 'A':
			moveRight = false;
			break;
		case 'D':
			moveLeft = false;
			break;
		case 'a':
			rotateRight = false;
			break;
		case 's':
			moveBackward = false;
			break;
		case 'd':
			rotateLeft = false;
			break;
		case 'w':
			moveForward = false;
			break;
		default:
			break;
	}
}


void myKeyboard(unsigned char key, int x, int y){
	switch(key) {
		case 'A':
			moveRight = true;
			break;
		case 'D':
			moveLeft = true;
			break;
		case 'a':
			rotateRight = true;
			break;
		case 's':
			moveBackward = true;
			break;
		case 'd':
			rotateLeft = true;
			break;
		case 'w':
			moveForward = true;
			break;
		case 'Q':; case 'q':
			exit(1);
			break;
		default:
			break;
	}
}


//---------------INIT APPLICAZIONE---------------------
void setPerspective(){
	gluPerspective(90.0, (float)windowWidth / (float)windowHeight, 0.1, 100.0); 
}

void myReshape(int w, int h){
	windowWidth = w;
	windowHeight = h;	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective();
}

void caricaTexture(){
//${CARICA_TEXTURE}
}

void gestisciIlluminazione(){
//${GESTISCI_ILLUMINAZIONE}
}

void init(){	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);
}

void centraFinestra(int windowWidth, int windowHeight){
	int desktopWidth = 1440;
	int desktopHeight = 900;

	int left = (desktopWidth-windowWidth)/2;
	int top = (desktopHeight-windowHeight)/2;

	glutInitWindowPosition(left,top);
	glutInitWindowSize(windowWidth,windowHeight);
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	centraFinestra(530,530);
	glutCreateWindow("Generated by SantoCAD");
	GLenum err = glewInit();
	if (GLEW_OK != err){
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glutIdleFunc(myIdle);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	init();
	caricaTexture();

	glutMainLoop();
	return(1);
}

