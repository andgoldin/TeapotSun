//#elif defined(__linux)
#if defined(__APPLE__) || defined(MACOSX)
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

#include <math.h>
#include <time.h>
#include "image_loader.h"
#include "texture_loader.h"


/* Class for a Galaxy object, for the purposes of background imagery.
 * Author: Andrew Goldin
 */
class Galaxy {

public:
	
	// The galaxy's constructors.
	Galaxy();
	Galaxy(float rad);

	// The default destructor.
	~Galaxy();

	// The galaxy's radius.
	float radius;

	// The galaxy's color, represnted as a list of RGB values.
	float color[3];

	// The galaxy's texture ID, for texturing purposes.
	GLuint textureID;

	// Sets the texture of the galaxy to the file with the given file name.
	void setTexture(const char* name);

	// Sets the key parameters of the galaxy's motion.
	void setParams(float rad);

	// Draws the galaxy and the associated grid.
	void draw();
	void drawGrid();

};