#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader_handler.h"
#include "texture_handler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gameModule
{
	class spriteRenderer
	{
	public:
		spriteRenderer(shaderHandler &shader);
		spriteRenderer(void);
		~spriteRenderer(void);

		void drawSprite(textureHandler &texture, glm::vec2 position,
			glm::vec2 size  = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
			glm::vec3 color = glm::vec3(1.0f));

	private:
		shaderHandler shader;
		unsigned int  quadVAO;

	private:
		void initRenderData(void);
	};
}

#endif