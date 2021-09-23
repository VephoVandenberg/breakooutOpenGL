#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H

#include <glm/glm.hpp>

#include "texture_handler.h"
#include "game_object.h"

namespace gameModule
{
	class ballObject : public gameObject 
	{
	public:
		float radius;
		bool stuck;

		bool sticky, passThrough;

	public:
		ballObject(void);
		ballObject(glm::vec2 pos, float radius, glm::vec2 velocity, textureHandler sprite);

		glm::vec2 	move(float dt, unsigned int windowWidth);
		void 		reset(glm::vec2 position, glm::vec2 velocity);

	};	
}

#endif