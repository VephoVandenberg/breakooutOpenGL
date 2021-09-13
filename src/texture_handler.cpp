#include "texture_handler.h"

using namespace gameModule;

textureHandler::textureHandler(const void *data,
			         const unsigned int width,
			         const unsigned int height)
                     : imageWidth(width), imageHeight(height), internalFormat(GL_RGB), imageFormat(GL_RGB), 
                       wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

    if (data)
    {
	   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	   glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
	   std::cout << "Failed to load"  << std::endl;
    }
}

void textureHandler::generate(unsigned int width, unsigned int height, unsigned char *data)
{
    imageWidth = width;
    imageHeight = height;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, imageWidth, imageHeight, 0, imageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void textureHandler::bindTexture(void) const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void textureHandler::unbindTexture(void) const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
