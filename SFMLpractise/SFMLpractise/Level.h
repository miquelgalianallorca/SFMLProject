#pragma once

#include "EngineIncludes.h"
#include "Tile.h"

class Character;
class Path;

class Level
{
public:
	Level(int rows, int cols);
	~Level();

	void Update(sf::RenderWindow &window, float deltaTime);
	void Draw(sf::RenderWindow &window, float alphaInterp);

private:
	int levelRows, levelCols;
	Tile **tiles;

	//Hover
	sf::Vector2i tileHoveredCoord, prevTileHoveredCoord;
	void Hover(sf::Vector2f worldPos);
	bool HoveringValidTile(sf::RenderWindow &window, sf::Vector2f worldPos);
	
	//Selecting
	bool tileSelected;
	sf::Vector2i selectedTileOrigin, selectedTileDestination;

	void Select(Tile &hoveredTile);
	void SelectTileOrigin(Tile &tile);
	void SelectTileDestination(Tile &tile);

	//Character
	Character *character;

	//Pathfinding
	Path *path;
};

