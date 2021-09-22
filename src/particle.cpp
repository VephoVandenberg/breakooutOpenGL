#include <random>
#include <iostream>

#include "particle.h"

using namespace gameModule;

particleGenerator::particleGenerator(shaderHandler shaderArg, textureHandler textureArg, unsigned int amountArg) :
										shader(shaderArg), texture(textureArg), amount(amountArg), lastUsedParticle(0)
{
	init();
	std::cout << "it comes here";
}

void particleGenerator::update(float dt, gameObject &gameObj, unsigned int newParticles, glm::vec2 offset)
{
	for (unsigned int i = 0; i < newParticles; i++)
	{
		int unusedParticle = firstUnusedParticle();
		respawnParticle(particles[unusedParticle], gameObj, offset);
	}

	for (unsigned int i = 0; i < amount; i++)
	{
		particle &temp = particles[i];
		temp.life -= dt;
		if (temp.life > 0.0f)
		{
			temp.position -= temp.velocity * dt;
			temp.color.a -= dt * 2.5f;
		}
	}
}

void particleGenerator::draw(void)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.use();

	for (particle part : particles)
	{
		if (part.life > 0.0f)
		{
			shader.setVector2f("offset", part.position);
			shader.setVector4f("color", part.color);
			texture.bindTexture();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void particleGenerator::init(void)
{
	unsigned int VBO;

	float particleVerts[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleVerts), particleVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < amount; i++)
	{
		particles.push_back(particle());
	}
}

unsigned int particleGenerator::firstUnusedParticle(void)
{
	for (unsigned int i = lastUsedParticle; i < amount; i++)
	{
		if (particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	for (unsigned int i = 0; i < lastUsedParticle; i++)
	{
		if (particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void particleGenerator::respawnParticle(particle &part, gameObject &obj, glm::vec2 offset)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	float color = 0.5f + (rand() % 100) / 100.0f;
	part.position = obj.position + random + offset;
	part.color = glm::vec4(color, color, color, 1.0f);
	part.life = 0.5f;
	part.velocity = obj.velocity * 0.1f;
}
