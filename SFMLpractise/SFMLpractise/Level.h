#pragma once

#include "EngineIncludes.h"
#include "Tile.h"
#include "AStar.h"

class Character;

class Level
{
public:
	Level(int rows, int cols);
	~Level();

	void HandleEvent(sf::Event &event);
	void Update(sf::RenderWindow &window, float deltaTime);
	void Draw(sf::RenderWindow &window, float alphaInterp);

private:
	int levelRows, levelCols;
	Tile **tiles;

	//Hover
	Tile *hoveredTile;
	sf::Vector2i tileHoveredCoord, prevTileHoveredCoord;
	void Hover(sf::Vector2f worldPos);
	bool HoveringValidTile(sf::RenderWindow &window, sf::Vector2f worldPos);
	
	//Selecting
	bool tileSelected, destinationSelected;
	sf::Vector2i selectedTileOrigin, selectedTileDestination;

	void SelectTileOrigin(Tile *tile);
	void SelectTileDestination(Tile *tile);

	//Path
	AStar::CoordinateList path;
	void CalculatePath();
	void CleanPath();

	//Character
	Character *character;
};

