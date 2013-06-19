//#elif defined(__linux)
#if defined(__APPLE__) || defined(MACOSX)
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

#include <math.h>
#include <time.h>
#include "texture_loader.h"


/* Class for a Planet object that contains the required simulation properties.
 * Author: Andrew Goldin
 */
class Planet {

public:
	
	// The planet's constructors. The default constructor produces random values.
	Planet();
	Planet(float dist, float rad, float rot, float rev);

	// The default destructor.
	~Planet();

	// The planet's distance from the Sun.
	float distance;

	// The planet's radius.
	float radius;

	// The planet's color, represnted as a list of RGB values.
	float color[3];

	// The current rotation speed and angle of the planet, with respect to it's axis.
	float rotationSpeed;
	float rotationAngle;

	// The current revolution speed and angle of the planet with respect to the sun.
	float revolutionSpeed;
	float revolutionAngle;

	// A speed multiplier, if it exists.
	float speedMult;

	// The planet's texture ID, for texturing purposes.
	GLuint textureID;

	// Sets the texture of the planet to the file with the given file name.
	void setTexture(const char* name);

	// Sets the key parameters of the planet's motion.
	void setParams(float dist, float rad, float rot, float rev);

	// Randomizes the planet's motion params.
	void randomize();

	// Changes the speed multiplier to a given value.
	void changeSpeed(float ds);

	// Draws the planet and its orbital path.
	void draw();
	void drawOrbitPath();

};


// The Asteroid class, which inherits from Planet
class Asteroid : public Planet {
public:
	// override the draw and randomize functions
	void draw();
	void randomize();
};