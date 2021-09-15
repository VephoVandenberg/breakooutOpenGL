#include <iostream>

#include "texture_handler.h"

using namespace gameModule;

textureHandler::textureHandler()
    : textureWidth(0), textureHeight(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
    glGenTextures(1, &textureID);
}

void textureHandler::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    textureWidth = width;
    textureHeight = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void textureHandler::bindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}