#include "galaxy.h"


Galaxy::Galaxy() {
	radius = 60.1f;
}

Galaxy::Galaxy(float rad) {
	radius = rad;
}


Galaxy::~Galaxy() { }


void Galaxy::setTexture(const char* name) {
	textureID = loadTexture(loadBMP(name));
}


void Galaxy::setParams(float rad) {
	radius = rad;
}


void Galaxy::draw() {
	glPushMatrix();

		glColor3f(0.5f, 0.5f, 0.5f);

		// enable texture mapping
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Prepare and draw the sphere itself
		GLUquadric* quad = gluNewQuadric();
		gluQuadricOrientation(quad, GLU_INSIDE);
		gluQuadricTexture(quad, GLU_TRUE);
		gluSphere(quad, radius, 40, 40);

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


void Galaxy::drawGrid() {
	glPushMatrix();
		glColor3f(0.4f, 0.4f, 0.4f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutWireSphere(radius - 0.05f, 20, 20);
	glPopMatrix();
}