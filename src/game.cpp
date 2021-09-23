#include <iostream>
#include <random>
#include <algorithm>

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
    resourceManager::loadShader("shaders/particle_vertex.vert", "shaders/particle_fragment.frag", nullptr, "particle");
    resourceManager::loadShader("shaders/post_processing.vert", "shaders/post_processing.frag", nullptr, "postProcessing");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(gameWidth), 
        static_cast<float>(gameHeight), 0.0f, 0.0f, 1.0f);

    resourceManager::getShader("sprite").use().setInteger("image", 0);
    resourceManager::getShader("sprite").setMatrix4("projection", projection);
    resourceManager::getShader("particle").use().setInteger("sprite", 0);
    resourceManager::getShader("particle").setMatrix4("projection", projection);

    resourceManager::loadTexture("textures/background.jpg",             false, "background");
    resourceManager::loadTexture("textures/block.png",                  false, "block");
    resourceManager::loadTexture("textures/block_solid.png",            false, "block_solid");
    resourceManager::loadTexture("textures/awesomeface.png",            true,  "face");
    resourceManager::loadTexture("textures/powerup_speed.png",          true,  "powerupSpeed");
    resourceManager::loadTexture("textures/powerup_sticky.png",         true,  "powerupSticky");
    resourceManager::loadTexture("textures/powerup_increase.png",       true,  "powerupSizeIncrease");
    resourceManager::loadTexture("textures/powerup_confuse.png",        true,  "powerupConfuse");
    resourceManager::loadTexture("textures/powerup_chaos.png",          true,  "powerupChaos");
    resourceManager::loadTexture("textures/powerup_passthrough.png",    true,  "powerupPassThrough");

    resourceManager::loadTexture("textures/paddle.png",      true,  "paddle");
    resourceManager::loadTexture("textures/particle.png",    true,  "particle");

    glm::vec2 playerPos = glm::vec2(gameWidth / 2.0f - PLAYER_SIZE.x / 2.0f, gameHeight - PLAYER_SIZE.y);
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    renderer = new spriteRenderer(resourceManager::getShader("sprite"));
    player = new gameObject(playerPos, PLAYER_SIZE, resourceManager::getTexture("paddle"), glm::vec3(1.0f));
    ball = new ballObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, resourceManager::getTexture("face"));
    particles = new particleGenerator(resourceManager::getShader("particle"), resourceManager::getTexture("particle"), 500);
    effects = new postProcessor(resourceManager::getShader("postProcessing").use(), gameWidth, gameHeight);

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

bool game::shouldSpawn(unsigned int chance)
{
    unsigned int random = rand() % chance;
    return random == 0;
}

void game::spawnPowerUps(gameObject &block)
{
    if (shouldSpawn(75))
    {
        powerUps.push_back(powerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.position, resourceManager::getTexture("powerupSpeed")));
    }

    if (shouldSpawn(75))
    {
        powerUps.push_back(powerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.position, resourceManager::getTexture("powerupSticky")));
    }

    if (shouldSpawn(75))
    {
        powerUps.push_back(powerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.position, resourceManager::getTexture("powerupPassThrough")));
    }

    if (shouldSpawn(75))
    {
        powerUps.push_back(powerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4f), 0.0f, block.position, resourceManager::getTexture("powerupSizeIncrease")));
    }

    if (shouldSpawn(15))
    {
        powerUps.push_back(powerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.position, resourceManager::getTexture("powerupConfuse")));
    }

    if (shouldSpawn(15))
    {
        powerUps.push_back(powerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.position, resourceManager::getTexture("powerupChaos")));
    }

}

void game::activatePowerUp(powerUp &power)
{
    if (power.type == "speed")
    {
        ball->velocity *= 1.2f;
    }

    else if  (power.type == "sticky")
    {
        ball->sticky = true;
        player->color = glm::vec3(1.0f, 0.5f, 1.0f);
    }

    else if  (power.type == "pass-through")
    {
        ball->passThrough = true;
        ball->color = glm::vec3(1.0f, 0.5f, 0.5f);
    }

    else if  (power.type == "pad-size-increase")
    {
        player->size.x += 50;
    }

    else if  (power.type == "chaos")
    {
        if (!effects->chaos)
        {
            effects->chaos = true;
        }
    }

    else if  (power.type == "confuse")
    {
        if (!effects->confuse)
        {
            effects->confuse = true;
        }
    }
}

bool game::isOtherPowerUpActive(std::vector<powerUp> &power, std::string type)
{
    for (const powerUp &power : powerUps)
    {
        if (power.activated)
        {
            if (power.type == type)
            {
                return true;
            }
        }
    }
    return false;
}

void game::updatePowerUps(float dt)
{
    for (powerUp &power : powerUps)
    {
        power.position += power.velocity * dt;
        if (power.activated)
        {
            power.duration -= dt;
            if (power.duration <= 0.0f)
            {
                power.activated = false;
                if (power.type == "sticky")
                {
                    if (!isOtherPowerUpActive(powerUps, "sticky"))
                    {
                        ball->sticky = false;
                        player->color = glm::vec3(1.0f);
                    }
                }
                else if (power.type == "pass-through")
                {
                    if (!isOtherPowerUpActive(powerUps, "passThrough"))
                    {
                        ball->passThrough = false;
                        ball->color = glm::vec3(1.0f);
                    }
                }
                else if (power.type == "chaos")
                {
                    if (!isOtherPowerUpActive(powerUps, "chaos"))
                    {
                        effects->chaos = false;
                    }
                }

                else if (power.type == "confuse")
                {
                    if (!isOtherPowerUpActive(powerUps, "confuse"))
                    {
                        effects->confuse = false;
                    }
                }
            }
        }
    }

    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), 
                    [](const powerUp &power) { return power.destroyed && !power.activated; }),
                     powerUps.end());
}

bool game::checkCollision(gameObject &firstObj, gameObject &secondObj)
{
    bool collideX = firstObj.position.x + firstObj.size.x >= secondObj.position.x &&
                      secondObj.position.x + secondObj.size.x >= firstObj.position.x;

    bool collideY = firstObj.position.y + firstObj.size.y >= secondObj.position.y &&
                      secondObj.position.y + secondObj.size.y >= firstObj.position.y;

    return collideX && collideY;
}

collision game::checkCollision(ballObject &firstObj, gameObject &secondObj)
{
    glm::vec2 circleCenter(firstObj.position + firstObj.radius);

    glm::vec2 recHalfExtents(secondObj.size.x / 2, secondObj.size.y / 2);
    glm::vec2 recCenter(secondObj.position.x + recHalfExtents.x,
                        secondObj.position.y + recHalfExtents.y);

    glm::vec2 difference = circleCenter - recCenter;
    glm::vec2 clamped = glm::clamp(difference, -recHalfExtents, recHalfExtents);

    glm::vec2 closest = recCenter + clamped;

    difference = closest - circleCenter;

    if (glm::length(difference) <= firstObj.radius)
    {
        return std::make_tuple(true, vectorDirection(difference), difference);
    }
    else
    {
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
    }
}

void game::doCollisions(void)
{
    for (gameObject &box : levels[level].bricks)
    {
        if (!box.destroyed)
        {
            collision coll = checkCollision(*ball, box);
            if (std::get<0>(coll))
            {
                if (!box.isSolid)
                {
                    box.destroyed = true;
                    spawnPowerUps(box);
                }
                else
                {
                    shakeTime = 0.05f;
                    effects->shake = true;
                }

                direction dir = std::get<1>(coll);
                glm::vec2 diffVector = std::get<2>(coll);

                if (!(ball->passThrough && !box.isSolid))
                {
                    if (dir == RIGHT || dir == LEFT)
                    {
                        ball->velocity.x = -ball->velocity.x;

                        float penetration = ball->radius - std::abs(diffVector.x);

                        if (dir == LEFT)
                        {
                            ball->position.x += penetration;
                        }
                        else
                        {
                            ball->position.x -= penetration;
                        }
                    }
                    else
                    {
                        ball->velocity.y = -ball->velocity.y;

                        float penetration = ball->radius - std::abs(diffVector.y);

                        if (dir == DOWN)
                        {
                            ball->position.y += penetration;
                        }
                        else
                        {
                            ball->position.y -= penetration;
                        }
                    }
                }

            }
        }
    }

    collision result = checkCollision(*ball, *player);

    if (std::get<0>(result) && !ball->stuck)
    {
        float centerPaddle = player->position.x + player->size.x / 2.0f;
        float distance = (ball->position.x + ball->radius) - centerPaddle;
        float percentage = distance / (player->size.x / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = ball->velocity;
        ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        // ball->velocity.y = -ball->velocity.y;
        ball->velocity.y = -1.0f * std::abs(ball->velocity.y);
        ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
        ball->stuck = ball->sticky;
    }

    for (powerUp &power : powerUps)
    {
        if (!power.destroyed)
        {
            if (power.position.y >= gameHeight)
            {
                power.destroyed = true;
            }
            if (checkCollision(*player, power))
            {
                activatePowerUp(power);
                power.destroyed = true;
                power.activated = true;
            }
        }
    }
}

direction game::vectorDirection(glm::vec2 target)
{
    glm::vec2 compass[4] = {
        glm::vec2(0.0f,  1.0f),
        glm::vec2(1.0f,  0.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f)
    };

    float max = 0.0f;
    unsigned int bestMatch = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return (direction)bestMatch;
}

void game::resetLevel(void)
{
    switch(level)
    {
        case 0:
        {
            levels[level].load("levels/one.lvl", gameWidth, gameHeight / 2);
        }break;


        case 1:
        {
            levels[level].load("levels/two.lvl", gameWidth, gameHeight / 2);
        }break;


        case 2:
        {
            levels[level].load("levels/three.lvl", gameWidth, gameHeight / 2);
        }break;


        case 3:
        {
            levels[level].load("levels/four.lvl", gameWidth, gameHeight / 2);
        }break;
    }
}

void game::resetPlayer(void)
{
    player->size = PLAYER_SIZE;
    player->position = glm::vec2(gameWidth / 2.0f - player->size.x / 2.0f, gameHeight - player->size.y);
    ball->reset(player->position + glm::vec2(player->size.x / 2.0f - ball->radius, -(2.0f * ball->radius)), INITIAL_BALL_VELOCITY);
    effects->chaos = effects->confuse = false;
    ball->passThrough = ball->sticky = false;
    player->color = glm::vec3(1.0f);
    ball->color = glm::vec3(1.0f);
}

void game::update(float dt)
{
    ball->move(dt, gameWidth);
    particles->update(dt, *ball, 1, glm::vec2(ball->radius / 2.0f));

    doCollisions();

    updatePowerUps(dt);

    if (ball->position.y >= gameHeight)
    {
        resetLevel();
        resetPlayer();
    }

    if (shakeTime > 0.0f)
    {
        shakeTime -= dt;
        if (shakeTime <= 0.0f)
        {
            effects->shake = false;
        }
    }
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
        effects->beginRender();
        renderer->drawSprite(resourceManager::getTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(gameWidth, gameHeight), 0.0f);

        levels[level].draw(*renderer);
        player->draw(*renderer);

        for (powerUp &power : powerUps)
        {
            if (!power.destroyed)
            {
                power.draw(*renderer);
            }
        }


        if (!ball->stuck)
        {
            particles->draw();
        }
        ball->draw(*renderer);
        effects->endRender();
        effects->render(glfwGetTime());
    }
}
