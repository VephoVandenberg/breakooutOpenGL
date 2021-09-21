#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sprite_renderer.h"
#include "game_level.h"
#include "game_object.h"
#include "ball_object.h"

namespace gameModule
{

	const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
	const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
	const float PLAYER_VELOCITY(500.0f);
	const float BALL_RADIUS = 12.5f;

	enum gameState {
	    GAME_ACTIVE,
	    GAME_MENU,
	    GAME_WIN
	};

	enum direction {
		UP,
		RIGHT,
		DOWN,
		LEFT 
	};

	typedef std::tuple<bool, direction, glm::vec2> collision;

	class game
	{
	public:
	    gameState               state;	
	    bool                    keys[1024];
	    unsigned int            gameWidth, gameHeight;
	    std::vector<gameLevel> 	levels;
	    unsigned int 			level;

	public:
	    game(unsigned int width, unsigned int height);
	    ~game(void);
	    void init(void);
	    void processInput(float dt);
	    void update(float dt);
	    void render(void);
	    void doCollisions(void);

	    bool checkCollision(gameObject &firstObj, gameObject &secondObj);
	    
	    collision checkCollision(ballObject &firstObj, gameObject &secondObj);
	    direction vectorDirection(glm::vec2 target);

	private:
		spriteRenderer  *renderer 	= NULL;
		gameObject 		*player 	= NULL;
		ballObject 		*ball 		= NULL;
	};
}
#endif