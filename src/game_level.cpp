#include <fstream>
#include <sstream>

#include "game_level.h"
#include "resource_manager.h"


using namespace gameModule;

gameLevel::gameLevel(void)
{

}
		
void gameLevel::load(const char *file, 
		  			 unsigned int levelWidth, unsigned int levelHeight)
{
	bricks.clear();

	unsigned int tileCode;
	gameLevel level;

	std::string line;
	std::ifstream fileStream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (fileStream)
	{
		while (std::getline(fileStream, line))
		{
			std::istringstream rowOfNumbers(line);
			std::vector<unsigned int> row;

			while (rowOfNumbers >> tileCode)
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
		{
			init(tileData, levelWidth, levelHeight);
		}
	}
}

void gameLevel::init(std::vector<std::vector<unsigned int>> tileData, 
					 unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int height = tileData.size();
	unsigned int width  = tileData[0].size();
	float unitWidth 	= levelWidth/static_cast<float>(width);
	float unitHeight 	= levelHeight/height;  	

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (tileData[y][x] == 1)
			{
				glm::vec2 pos(unitWidth*x, unitHeight*y);
				glm::vec2 size(unitWidth, unitHeight);
				gameObject object(pos, size,
						   		  resourceManager::getTexture("block_solid"),
						   		  glm::vec3(0.8f, 0.8f, 0.7f));
				object.isSolid = true;
				bricks.push_back(object);
			}
			else if (tileData[y][x] > 1)
			{
				glm::vec3 color = glm::vec3(1.0f);
				switch (tileData[y][x])
				{
					case 2:
					{
						color = glm::vec3(0.2f, 0.6f, 1.0f);
					}break;

					case 3:
					{
						color = glm::vec3(0.0f, 0.7f, 0.0f);
					}break;

					case 4:
					{
						color = glm::vec3(0.4f, 0.9f, 0.5f);
					}break;

					case 5:
					{
						color = glm::vec3(1.0f, 0.5f, 0.0f);
					}break;

					default:
					{

					}break;
				}

				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				bricks.push_back(gameObject(pos, size, resourceManager::getTexture("block"), color));
			}
		}
	}
}		

void gameLevel::draw(spriteRenderer &renderer)
{
	for (gameObject &tile : bricks)
	{
		if (!tile.destroyed)
		{
			tile.draw(renderer);
		}
	}
}

bool gameLevel::isCompleted(void)
{
	for (gameObject &tile : bricks)
	{
		if (!tile.isSolid && !tile.destroyed)
		{
			return false;
		}
	}

	return true;	
}
