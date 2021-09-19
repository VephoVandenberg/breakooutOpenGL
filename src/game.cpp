#include <iostream>

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

    resourceManager::loadTexture("textures/background.jpg",  false, "background");
    resourceManager::loadTexture("textures/awesomeface.png", true,  "face");
    resourceManager::loadTexture("textures/block.png",       false,  "block");
    resourceManager::loadTexture("textures/block_solid.png", false,  "block_solid");

    gameLevel one, two, three, four;
    one.load("levels/one.lvl",      gameWidth, gameHeight / 2);
    two.load("levels/two.lvl",      gameWidth, gameHeight / 2);
    three.load("levels/three.lvl",  gameWidth, gameHeight / 2);
    four.load("levles/four.lvl",    gameWidth, gameHeight / 2);

    levels.push_back(one);
    levels.push_back(two);
    levels.push_back(three);
    levels.push_back(four);
    level = 0;
}

void game::update(float dt)
{
    
}

void game::processInput(float dt)
{
   
}

void game::render()
{
    if (state == GAME_ACTIVE)
    {
        renderer->drawSprite(resourceManager::getTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(gameWidth, gameHeight), 0.0f);

        levels[level].draw(*renderer);
    }
}
