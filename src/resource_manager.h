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
	    // resource storage
	    static std::map<std::string, shaderHandler>    shaders;
	    static std::map<std::string, textureHandler> Textures;
	    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	    static shaderHandler    loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	    // retrieves a stored sader
	    static shaderHandler    getShader(std::string name);
	    // loads (and generates) a texture from file
	    static textureHandler loadTexture(const char *file, bool alpha, std::string name);
	    // retrieves a stored texture
	    static textureHandler getTexture(std::string name);
	    // properly de-allocates all loaded resources
	    static void clear();
	private:
	    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	    resourceManager() { }
	    // loads and generates a shader from file
	    static shaderHandler    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	    // loads a single texture from file
	    static textureHandler loadTextureFromFile(const char *file, bool alpha);
	};
}
#endif