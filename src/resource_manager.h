#ifndef REOSURCE_MANAGER_H
#define REOSURCE_MANAGER_H

#include <string>
#include <map>

#include "shader_handler.h"
#include "texture_handler.h"

namespace gameModule
{
	class resourceManager
	{
	private:
		resourceManager(void);
		resourceManager(const resourceManager& resourceManagerInstance);
		resourceManager(resourceManager&& resourceManagerInstance);

	public:
		static shaderHandler getShaderHandler(std::string name);
		static textureHandler getTextureHandler(std::string name);

		static shaderHandler  loadShader(const char *vShaderFile, const char *fShaderHandler, const char *gShaderFile, std::string name);
		static textureHandler loadTexture(const char *textureFile, bool alpha, std::string name);

		static void clear(void);

		static std::map<std::string, textureHandler> textures;
		static std::map<std::string, shaderHandler> shaders;

	private:		
		static shaderHandler loadShaderFromFile(const char *vShaderFile, const char *fShaderHandler, const char *gShaderFile = nullptr);
		static textureHandler loadTextureFromFile(const char *textureFile, bool alpha);
	};
}

#endif