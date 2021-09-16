#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "game_object.h"

namespace gameModule
{
	class gameLevel
	{
	public:
		std::vector<gameObject> bricks;

	public:
		gameLevel(void);
		void load(const char *file, 
			unsigned int levelWidth, unsigned int levelHeight);
		void draw(spriteRenderer *renderer);
		bool isCompleted(void);

	private:
		void init(std::vector<std::vector<unsigned int>> tileData, 
			unsigned int levelWidth, unsigned int levelHeight);
	};
}

#endif