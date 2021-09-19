#ifndef GAME_H
#define GAME_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sprite_renderer.h"
#include "game_level.h"


namespace gameModule
{
	enum gameState {
	    GAME_ACTIVE,
	    GAME_MENU,
	    GAME_WIN
	};

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
	    ~game();
	    void init();
	    void processInput(float dt);
	    void update(float dt);
	    void render();
	    
	private:
		spriteRenderer  *renderer = NULL;
	};
}
#endif