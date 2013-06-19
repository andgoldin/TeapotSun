#include "texture_loader.h"


// loads an image that was created from a file into a 2D texture for texture mapping
// created with the aid of Bill Jacobs at videotutorialsrock.com
GLuint loadTexture(Image* img) {
	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);

	return texId; // Returns the id of the texture
}