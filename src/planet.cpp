#include "planet.h"


Planet::Planet() {
	speedMult = 1.0f;
	randomize();
}


Planet::Planet(float dist, float rad, float rot, float rev) {
	setParams(dist, rad, rot, rev);
}


Planet::~Planet() { }


void Planet::changeSpeed(float n) {
	speedMult = pow(2, n - 1);
}


void Planet::setTexture(const char* name) {
	textureID = loadTexture(loadBMP(name));
}


void Planet::setParams(float dist, float rad, float rot, float rev){
	distance = dist;
	radius = rad;
	for (int i = 0; i < 3; i++) {
		color[i] = 1.0f; // color doesn't really matter, set it to white
	}
	rotationSpeed = rot;
	revolutionSpeed = rev;
}


void Planet::randomize() {
	distance = (float) (rand() % 50) + 3;
	radius = (float) (rand() % 10) / 20.0 + 0.15;
	revolutionSpeed = (float) (rand() % 10) / 150.0 + 0.05;
	revolutionAngle = (float) (rand() % 360);
	rotationSpeed = (float) (rand() % 10) / 5.0 + 0.1;
	rotationAngle = 0.0f;
}


void Planet::draw() {
	float angle = 2.0f * 3.1415926f;
	glPushMatrix();

		glColor3f(1, 1, 1);

		// enable texture mapping for the planet
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// rotate to the current revolution angle
		glRotatef(revolutionAngle, 0.0, 1.0, 0.0);

		// Translate out to the orbital radius
		glTranslatef(distance * cosf(angle), 0, distance * sinf(angle));

		// rotate to the current rotation angle
		glRotatef(rotationAngle, 0.0, 1.0, 0.0);

		// Prepare and draw the sphere itself
		GLUquadric* quad = gluNewQuadric();
		gluQuadricOrientation(quad, GLU_OUTSIDE);
		gluQuadricTexture(quad, GLU_TRUE);
		gluSphere(quad, radius, 40, 40);

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	// Update the revolution and rotation angles for the next call
	revolutionAngle += revolutionSpeed * speedMult;
	if (revolutionAngle >= 360.0f) {
		revolutionAngle -= 360.0f;
	}
	rotationAngle += rotationSpeed * speedMult;
	if (rotationAngle >= 360.0f) {
		rotationAngle -= 360.0f;
	}
}


void Planet::drawOrbitPath() {
	int segments = 50;
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7); // circles will be gray-ish
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i < segments; i++) { 
			float angle = 2.0f * 3.1415926f * float(i) / float(segments); // get the current angle 
			float x = distance * cosf(angle); // calculate the x component 
			float z = distance * sinf(angle); // calculate the z component 
			glVertex3f(x, 0, z); // output vertices
		} 
		glEnd(); 
	glPopMatrix();
}


void Asteroid::draw() {
	float angle = 2.0f * 3.1415926f;
	glPushMatrix();

		glColor3f(color[0], color[1], color[2]);

		// rotate to the current revolution angle
		glRotatef(revolutionAngle, 0.0, 1.0, 0.0);

		// Translate out to the orbital radius
		glTranslatef(distance * cosf(angle), 0, distance * sinf(angle));

		// rotate to the current rotation angle
		glRotatef(rotationAngle, 1.0, 1.0, 1.0);

		// Prepare and draw the sphere itself
		glutSolidTeapot(radius);

	glPopMatrix();

	// Update the revolution and rotation angles for the next call
	revolutionAngle += revolutionSpeed * speedMult;
	if (revolutionAngle >= 360.0f) {
		revolutionAngle -= 360.0f;
	}
	rotationAngle += rotationSpeed * speedMult;
	if (rotationAngle >= 360.0f) {
		rotationAngle -= 360.0f;
	}
}



void Asteroid::randomize() {
	for (int i = 0; i < 3; i++) {
		color[i] = (float) (rand() / (float) RAND_MAX );
	}
	radius = (float) (rand() % 10) / 25.0 + 0.1;
	revolutionSpeed = (float) (rand() % 5) / 150.0 + 0.05;
	revolutionAngle = (float) (rand() % 360);
	rotationSpeed = (float) (rand() % 10) / 5.0 + 0.1;
	rotationAngle = 0.0f;
}