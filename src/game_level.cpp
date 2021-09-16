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
		while (std::getline(fstream, line))
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
	float unitHeight 	= levelHeight/static_cast<float>(height);  	

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
						   		  glm::vec3(0.5f, 0.3f, 0.2f));
				object.isSolid = true;
				bricks.push_back(object);
			}
			else if (tileData[y][x] > 1)
			{
				glm::vec3 color = glm::vec3(1.0f);
				switch (tileData[y][x])
				{
					case 2:
					{}break;

					case 3:
					{}break;

					case 4:
					{}break;

					case 5:
					{}break;
				}
			}
		}
	}
}		

void gameLevel::draw(spriteRenderer *renderer)
{

}

bool gameLevel::isCompleted(void)
{

}
