#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <iostream>

namespace gameModule
{
	class textureHandler
	{
	public:
	    unsigned int internalFormat;
	    unsigned int imageFormat;

	    unsigned int imageWidth, imageHeight;

	    unsigned int wrapS;
	    unsigned int wrapT;

	    unsigned int filterMin;
	    unsigned int filterMax;

	public:
	    textureHandler(const void *data,
			   const unsigned int width,
			   const unsigned int height);
	    textureHandler();

	    void generate(unsigned int width, unsigned int height, unsigned char *data);
	    void bindTexture(void) const;
	    void unbindTexture(void) const;

	    unsigned int *getID(void);

	private:
	    unsigned int textureID;

	};
}
#endif
