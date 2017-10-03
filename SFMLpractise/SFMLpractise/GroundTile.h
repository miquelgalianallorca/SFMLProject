#pragma once

#include "Tile.h"

class GroundTile :	public Tile
{

public:
	GroundTile(sf::Color colorFill, sf::Color colorOutline, sf::Vector2f pos, int size);
	~GroundTile();

	void Draw(sf::RenderWindow &window);

private:
	sf::Sprite* sprite;
};

