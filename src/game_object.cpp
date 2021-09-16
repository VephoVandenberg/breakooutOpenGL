#include "game_object.h"

using namespace gameModule;

gameObject::gameObject(glm::vec2 pos, glm::vec2 sizeArg, 
					   textureHandler spriteArg, 
					   glm::vec3 colorArg, glm::vec2 velocity) :
					position(pos), size(sizeArg), velocity(velocity), color(colorArg), rotation(0.0f), sprite(spriteArg), isSolid(false), destroyed(false)
{

}

gameObject::gameObject(void) :
	position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false)
{

}

void gameObject::draw(spriteRenderer& renderer)
{
	renderer.drawSprite(sprite, position, size, rotation, color);
}