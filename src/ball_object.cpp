#include "ball_object.h"

using namespace gameModule;

ballObject::ballObject(void) :
	gameObject(), radius(12.5f), stuck(true)
{

}

ballObject::ballObject(glm::vec2 pos, float radiusArg, glm::vec2 velocityArg, textureHandler spriteArg) :
	gameObject(pos, glm::vec2(radiusArg * 2.0f, radiusArg * 2.0f),  spriteArg, glm::vec3(1.0f), velocityArg), radius(radiusArg)
{

}

glm::vec2 ballObject::move(float dt, unsigned int windowWidth)
{
	if (!stuck)
	{
		position += velocity * dt;

		if (position.x <= 0.0f)
		{
			velocity.x = -velocity.x;
			position.x = 0.0f;
		}
		else if (position.x + size.x >= windowWidth)
		{
			velocity.x = -velocity.x;
			position.x = windowWidth - size.x;
		}

		if (position.y <= 0.0f)
		{
			velocity.y = -velocity.y;
			position.y = 0.0f;
		}
	}

	return position;
}

void ballObject::reset(glm::vec2 positionArg, glm::vec2 velocityArg)
{
	position = positionArg;
	velocity = velocityArg;
	stuck = true;
}