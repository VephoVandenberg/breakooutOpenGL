#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.

namespace gameModule
{
	class textureHandler
	{
	public:
	    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
	    unsigned int textureID;
	    // texture image dimensions
	    unsigned int textureWidth, textureHeight; // width and height of loaded image in pixels
	    // texture Format
	    unsigned int internalFormat; // format of texture object
	    unsigned int imageFormat; // format of loaded image
	    // texture configuration
	    unsigned int wrapS; // wrapping mode on S axis
	    unsigned int wrapT; // wrapping mode on T axis
	    unsigned int filterMin; // filtering mode if texture pixels < screen pixels
	    unsigned int filterMax; // filtering mode if texture pixels > screen pixels
	    // constructor (sets default texture modes)
	    textureHandler(void);
	    // generates texture from image data
	    void generate(unsigned int width, unsigned int height, unsigned char* data);
	    // binds the texture as the current active GL_TEXTURE_2D texture object
	    void bindTexture(void) const;
	};
}
#endif