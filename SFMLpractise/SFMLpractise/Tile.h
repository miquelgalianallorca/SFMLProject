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

	void MarkHover(); //Change color to hoverColor
	void UnmarkHover(); //Change color from hoverColor to normal or selected

	void MarkLeftClick(); //Change color to selectedColorL
	void MarkRightClick(); //Change color to selectedColorR
	void UnmarkClick(); //Change color to default color

	void MarkPath();
	void UnmarkPath();
	bool GetIsInPath();

	sf::Vector2f GetPosition();

private:
	void SetupRect();

	sf::Color tileFilledColor, tileOutlineColor;
	sf::Vector2f tilePosition;
	int tileSize;
	sf::RectangleShape rect;

	//Selection
	bool isSelectedL = false;
	bool isSelectedR = false;
	sf::Color selectedColorL = sf::Color::Magenta;
	sf::Color selectedColorR = sf::Color::Yellow;

	//Path
	bool isInPath = false;
};
