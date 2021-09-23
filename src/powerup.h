#ifndef POWERUP_H
#define POWERUP_H

#include <glm/glm.hpp>
#include <string>

#include "game_object.h"
#include "texture_handler.h"

namespace gameModule
{
	const glm::vec2 SIZE(60.0f, 20.0f);
	const glm::vec2 VELOCITY(0.0f, 150.0f);

	class powerUp : public gameObject
	{
	public:
		std::string type;
		float 		duration;
		bool 		activated;

	public:
		powerUp(std::string type, glm::vec3 color, float duration, glm::vec2 position, textureHandler texture)
			   : gameObject(position, SIZE, texture, color, VELOCITY), type(type), duration(duration), activated()
		{}
	};
}

#endif
