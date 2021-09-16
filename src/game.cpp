#include "game.h"
#include "resource_manager.h"

using namespace gameModule;

game::game(unsigned int width, unsigned int height) 
    : state(GAME_ACTIVE), keys(), gameWidth(width), gameHeight(height)
{ 

}

game::~game()
{
    delete renderer;
}

void game::init()
{
    resourceManager::loadShader("shaders/sprite_vertex_shader.vert", "shaders/sprite_fragment_shader.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(gameWidth), 
        static_cast<float>(gameHeight), 0.0f, -1.0f, 1.0f);
    resourceManager::getShader("sprite").use().setInteger("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    renderer = new spriteRenderer(resourceManager::getShader("sprite"));
    resourceManager::loadTexture("textures/awesomeface.png", true, "face");
}

void game::update(float dt)
{
    
}

void game::processInput(float dt)
{
   
}

void game::render()
{
    renderer->drawSprite(resourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
