/* TEAPOT SUN v2.0 (textured solar system generator)
	by ANDREW GOLDIN (adg2160) */

//#elif defined(__linux)
#if defined(__APPLE__) || defined(MACOSX)
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "planet.h"
#include "galaxy.h"

//using namespace std;

// values for mouse movement and camera control
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float lastx, lasty;

// values for planets
const int num_planets = 8; // number of planets in system
const int num_asteroids = 10; // number of asteroids in the teapot belt
float asteroids_distance;

Galaxy galaxy;
Planet sun;
Planet planets[num_planets];
Asteroid asteroids[num_asteroids];

float speedMult; // the movement speed multiplier, affected by keyboard input

bool* keyStates = new bool[256]; // boolean array to track multiple keypresses


// sets the initial values for each planet and teapot at random
void reset (void) {
	for (int i = 0; i < 256; i++) keyStates[i] = false; // no keys pressed at start

	// set the properties of each planet
	for (int i = 0; i < num_planets; i++) {
		planets[i].randomize();
	}

	asteroids_distance = (float) (rand() % 50) + 3;
	for (int i = 0; i < num_asteroids; i++) {
		asteroids[i].randomize();
		asteroids[i].distance = asteroids_distance;
	}

}


// KEYBOARD INPUT ("WASD" control)
void keyOperations (void) {
	// move forward by holding 'w'
	if (keyStates['w'] && !keyStates['s']) {
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad)) / 10;
		zpos -= float(cos(yrotrad)) / 10;
		ypos -= float(sin(xrotrad)) / 10;
	}
	// move backward by holding 's'
	if (keyStates['s'] && !keyStates['w']) {
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f); 
		xpos -= float(sin(yrotrad)) / 10;
		zpos += float(cos(yrotrad)) / 10;
		ypos += float(sin(xrotrad)) / 10;
	}
	// strafe right by holding 'd'
	if (keyStates['d'] && !keyStates['a']) {
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad)) * 0.1;
		zpos += float(sin(yrotrad)) * 0.1;
	}
	// strafe left by holding 'a'
	if (keyStates['a'] && !keyStates['d']) {
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 0.1;
		zpos -= float(sin(yrotrad)) * 0.1;
	}
	// hit 'g' to generate a new system
	if (keyStates['g']) { reset(); }
	// hit Esc to quit
	if (keyStates[27]) { exit(0); }
}


// enables various protocols for rendering
void initRendering(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); // set the shader to smooth shader
}


// loads the sun texture and all planet textures into the system
void loadScene(void) {
	// set the parameters of sun and galaxy
	sun = Planet(0.0f, 1.5f, 0.01f, 0.0f);
	galaxy = Galaxy(60.0f);

	// load all of the textures
	sun.setTexture("res/sun.bmp");
	planets[0].setTexture("res/planet_0.bmp");
	planets[1].setTexture("res/planet_1.bmp");
	planets[2].setTexture("res/planet_2.bmp");
	planets[3].setTexture("res/planet_3.bmp");
	planets[4].setTexture("res/planet_4.bmp");
	planets[5].setTexture("res/planet_5.bmp");
	planets[6].setTexture("res/planet_6.bmp");
	planets[7].setTexture("res/planet_7.bmp");
	galaxy.setTexture("res/galaxy.bmp");

	// initialize the speed multiplier
	speedMult = 1.0;
}


// camera rotation and translation commands for user interaction
void updateCamera (void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on the x-axis (left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera
}


// draws all objects in the scene
void drawScene(void) {
	galaxy.draw();
	if (!keyStates[' ']) {
		galaxy.drawGrid();
	}
	sun.draw();
	for (int i = 0; i < num_planets; i++) {
		planets[i].draw();
		if (!keyStates[' ']) planets[i].drawOrbitPath();
	}
	for (int i = 0; i < num_asteroids; i++) {
		asteroids[i].draw();
		if (!keyStates[' ']) asteroids[0].drawOrbitPath();
	}
}


// display our solar system
void display (void) {
	keyOperations(); // set the keypress operations
	glClearColor (0.0, 0.0, 0.0, 1.0); // clear the screen to black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color buffer and the depth buffer

	// enable the accumulation buffer for motion blur
    glAccum(GL_RETURN, 0.85f);
    glClear(GL_ACCUM_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, 0, -10);

	updateCamera(); // set our camera position
	
	drawScene(); // draw the scene

    glAccum(GL_ACCUM, 0.6f);
	glFlush();
	glutSwapBuffers(); // swap the buffers
}


// GL reshape function
void reshape (int w, int h) {
	// set the viewport to the current window specifications
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	// set the matrix to projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the perspective (angle of sight, width, height, depth)
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 100.0);
	// set the matrix back to model
	glMatrixMode(GL_MODELVIEW);
}


// set a keypressed state to true while key is held down
void keyPressed (unsigned char key, int x, int y) {  
	// Set the state of the current key to pressed
	keyStates[key] = true;
	
	// set speed of system with number keys. exponential increase!
	int speedChange = key - '0';
	if (speedChange > 0 && speedChange < 10) {
		sun.changeSpeed(speedChange);
		for (int i = 0; i < num_planets; i++) {
			planets[i].changeSpeed(speedChange);
		}
		for (int i = 0; i < num_asteroids; i++) {
			asteroids[i].changeSpeed(speedChange);
		}
	}
}  


// set a keypressed state to false when key is released
void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
} 


// mouse movement for camera control
void mouseMovement(int x, int y) {
	int diffx = x - lastx; // check the difference between the current x and the last x position
	int diffy = y - lasty; // check the difference between the current y and the last y position
	lastx = x; // set lastx to the current x position
	lasty = y; // set lasty to the current y position
	xrot += (float) diffy / 10; // set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx / 10; // set the yrot to yrot with the addition of the difference in the x position
}


// main function
int main (int argc, char **argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_ACCUM); 
	glutInitWindowSize(960, 540); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow("TeapotSun - adg2160");
	initRendering();
	
	loadScene();
	reset(); // set all initial values

	// OPTIONAL for entering fullscreen mode
	//glutGameModeString( "1920×1080:32@75" );
	//glutEnterGameMode();

	glutDisplayFunc(display); 
	glutIdleFunc(display); 
	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMovement); // click mouse to enable camera control
	glutKeyboardFunc(keyPressed);   
	glutKeyboardUpFunc(keyUp); 

	//glutSetCursor(GLUT_CURSOR_NONE); // hide mouse cursor

	glutMainLoop();
	return 0;
}