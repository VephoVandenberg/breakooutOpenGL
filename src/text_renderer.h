#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture_handler.h"
#include "shader_handler.h"

namespace gameModule
{

	struct character
	{
		unsigned int textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	class textRenderer
	{
	public:
		std::map<char, character> characters;     
    	shaderHandler textShader;

    public:
	    textRenderer(unsigned int width, unsigned int height, shaderHandler shader);
	    void load(std::string font, unsigned int fontSize);
	    void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

	private:
		unsigned int VAO, VBO;
	};
}

#endif