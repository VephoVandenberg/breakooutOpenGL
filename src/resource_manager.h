#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture_handler.h"
#include "shader_handler.h"

namespace gameModule
{
class resourceManager
{
	public:
	    static std::map<std::string, shaderHandler>    shaders;
	    static std::map<std::string, textureHandler> Textures;

	public:
	    static shaderHandler    loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	    static shaderHandler    getShader(std::string name);

	    static textureHandler loadTexture(const char *file, bool alpha, std::string name);
	    static textureHandler getTexture(std::string name);
	    static void clear();

	private:
	    resourceManager();
	    static shaderHandler  loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	    static textureHandler loadTextureFromFile(const char *file, bool alpha);
	};
}
#endif