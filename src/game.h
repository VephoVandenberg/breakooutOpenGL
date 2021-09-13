#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gameModule
{
	enum gameState
	{
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	class game
	{
	public:
		gameState 	 state;
		bool 		 keys[1024];
		unsigned int screenWidth, screenHeight;

	public:
		game(unsigned int width, unsigned int height);
		~game(void);

		void init(void);
		void processInput(float dt);
		void update(float dt);
		void render(void);

	private:
		game(const game& gameInstance);
		game(game&& gameInstance);
	};
}

#endif