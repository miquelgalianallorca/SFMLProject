#pragma once
#include "EngineIncludes.h"

class Tile
{
public:
	Tile();
	Tile(sf::Color colorFill, sf::Color colorOutline, sf::Vector2f pos, int size);
	Tile(sf::Vector2f pos, int size);
	~Tile();

	void Draw(sf::RenderWindow& window);

	void MarkHover();
	void UnmarkHover();

	sf::Vector2f GetPosition();

private:
	void SetupRect();

	sf::Color tileFilledColor, tileOutlineColor;
	sf::Vector2f tilePosition;
	int tileSize;
	sf::RectangleShape rect;
};
