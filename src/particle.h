#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/glew.h>

#include "shader_handler.h"
#include "texture_handler.h"
#include "game_object.h"

namespace gameModule
{
	struct particle
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 color;

		float life;

		particle(void) :
			position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
	};

	class particleGenerator
	{
	public:
		particleGenerator(shaderHandler shaderArg, textureHandler textureArg, unsigned int amountArg);
		void update(float dt, gameObject &gameObj, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
		void draw(void);

	private:
		std::vector<particle> particles;
		textureHandler texture;
		shaderHandler shader;
		unsigned int amount 			= 0;
		unsigned int VAO			 	= 0;
		unsigned int lastUsedParticle 	= 0;

	private:
		void init(void);
		unsigned int firstUnusedParticle(void);
		void respawnParticle(particle &part, gameObject &obj, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	};
}

#endif