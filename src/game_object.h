#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture_handler.h"
#include "sprite_renderer.h"

namespace gameModule
{
	class gameObject
	{
	public:
		glm::vec2 position;
		glm::vec2 size;
		glm::vec2 velocity;

		glm::vec3 color;

		float rotation;
		bool isSolid;
		bool destroyed;

		textureHandler sprite;

	public:
		gameObject(void);
		gameObject(glm::vec2 pos, glm::vec2 size, 
			textureHandler spriteArg, 
			glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

		virtual void draw(spriteRenderer& renderer);
	};
}

#endif