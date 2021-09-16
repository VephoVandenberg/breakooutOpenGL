#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>


namespace gameModule
{
	class textureHandler
	{
	public:
	    unsigned int textureID;
	    unsigned int textureWidth, textureHeight; // width and height of loaded image in pixels
	    unsigned int internalFormat; // format of texture object
	    unsigned int imageFormat; // format of loaded image

	    unsigned int wrapS; // wrapping mode on S axis
	    unsigned int wrapT; // wrapping mode on T axis
	    unsigned int filterMin; // filtering mode if texture pixels < screen pixels
	    unsigned int filterMax; // filtering mode if texture pixels > screen pixels
	    
	public:
	    textureHandler(void);
	    // generates texture from image data
	    void generate(unsigned int width, unsigned int height, unsigned char* data);
	    // binds the texture as the current active GL_TEXTURE_2D texture object
	    void bindTexture(void) const;
	};
}
#endif