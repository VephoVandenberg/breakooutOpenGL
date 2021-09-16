#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture_handler.h"
#include "shader_handler.h"

namespace gameModule
{
	class spriteRenderer
	{
	public:
	    spriteRenderer(shaderHandler &shaderArg);
	    ~spriteRenderer();

	    void drawSprite(textureHandler &texture, glm::vec2 position,
	     glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
	     glm::vec3 color = glm::vec3(1.0f));

	private:
	    shaderHandler shader; 
	    unsigned int  quadVAO;
	    void initRenderData();
	};
}
#endif