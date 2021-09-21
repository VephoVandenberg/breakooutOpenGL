#include <iostream>

#include "game.h"
#include "resource_manager.h"

using namespace gameModule;

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float PLAYER_VELOCITY(500.0f);
const float BALL_RADIUS = 12.5f;

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
        static_cast<float>(gameHeight), 0.0f, 0.0f, 1.0f);

    resourceManager::getShader("sprite").use().setInteger("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);


    resourceManager::loadTexture("textures/background.jpg",  false, "background");
    resourceManager::loadTexture("textures/block.png",       false, "block");
    resourceManager::loadTexture("textures/block_solid.png", false, "block_solid");
    resourceManager::loadTexture("textures/awesomeface.png", true,  "face");

    resourceManager::loadTexture("textures/paddle.png",      true,  "paddle");

    glm::vec2 playerPos = glm::vec2(gameWidth / 2.0f - PLAYER_SIZE.x / 2.0f, gameHeight - PLAYER_SIZE.y);
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    renderer = new spriteRenderer(resourceManager::getShader("sprite"));
    player = new gameObject(playerPos, PLAYER_SIZE, resourceManager::getTexture("paddle"), glm::vec3(1.0f));
    ball = new ballObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, resourceManager::getTexture("face"));

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

bool game::checkCollision(gameObject &firstObj, gameObject &secondObj)
{
    bool collideX = firstObj.position.x + firstObj.size.x >= secondObj.position.x &&
                      secondObj.position.x + secondObj.size.x >= firstObj.position.x;

    bool collideY = firstObj.position.y + firstObj.size.y >= secondObj.position.y &&
                      secondObj.position.y + secondObj.size.y >= firstObj.position.y;

    return collideX && collideY;
}

void game::doCollisions(void)
{
    for (gameObject &box : levels[level].bricks)
    {
        if (!box.destroyed)
        {
            if (checkCollision(*ball, box))
            {
                if (!box.isSolid)
                {
                    box.destroyed = true;
                }
                else
                {
                    ball->velocity.y = -ball->velocity.y;
                }
            }
        }
    }
}

void game::update(float dt)
{
    ball->move(dt, gameWidth);
    doCollisions();
}

void game::processInput(float dt)
{
    if (state == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;

        if (keys[GLFW_KEY_A])
        {
            if (player->position.x >= 0.0f)
            {
                player->position.x -= velocity;
                if (ball->stuck)
                {
                    ball->position.x -= velocity;
                }
            }
        }

        if (keys[GLFW_KEY_D])
        {
            if (player->position.x <= gameWidth - player->size.x)
            {
                player->position.x += velocity;
                if (ball->stuck)
                {
                    ball->position.x += velocity;
                }
            }
        }

        if (keys[GLFW_KEY_SPACE])
        {
            ball->stuck = false;
        }
    }
}

void game::render()
{
    if (state == GAME_ACTIVE)
    {
        renderer->drawSprite(resourceManager::getTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(gameWidth, gameHeight), 0.0f);

        levels[level].draw(*renderer);
        player->draw(*renderer);
        ball->draw(*renderer);
    }
}
