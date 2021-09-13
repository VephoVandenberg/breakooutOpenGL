#include "resource_manager.h"
#include "stb_image_loader.h"

#include <fstream>

using namespace gameModule;

std::map<std::string, shaderHandler> resourceManager::shaders;
std::map<std::string, textureHandler> resourceManager::textures;

shaderHandler resourceManager::getShaderHandler(std::string name)
{
	return shaders[name];
}

textureHandler resourceManager::getTextureHandler(std::string name)
{
	return textures[name];
}

shaderHandler  resourceManager::loadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

textureHandler resourceManager::loadTexture(const char *textureFile, bool alpha, std::string name)
{
	textures[name] = loadTextureFromFile(textureFile, alpha);
	return textures[name];
}

shaderHandler resourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile)
		{
			std::ifstream geomrtryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geomrtryShaderFile.rdbuf();
			geomrtryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	const char *gShaderCode = geometryCode.c_str();

	shaderHandler shader;
	shader.compile(vShaderCode, fShaderCode, gShaderCode != nullptr ? gShaderCode : nullptr);

	return shader;
}

textureHandler resourceManager::loadTextureFromFile(const char *textureFile, bool alpha)
{
	textureHandler texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	int width, height, nrChannels;
	unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	texture.generate(width, height, data);
	stbi_image_free(data);

	return texture;
}

void resourceManager::clear(void)
{
	for (auto shader: shaders)
	{
		glDeleteProgram(shader.second.getID());
	}

	for (auto texture: textures)
	{
		glDeleteTextures(1, texture.second.getID());
	}
}
