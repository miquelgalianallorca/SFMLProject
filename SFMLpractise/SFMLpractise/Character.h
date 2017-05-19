#pragma once
#include "EngineIncludes.h"

class Tile;

class Character
{
public:
	Character(Tile &startTile);
	~Character();

	void Draw(sf::RenderWindow &window, float alphaInterp);
	void Update(float deltaTime);

private:
	Tile &currentTile;
	sf::RectangleShape rect;

	float moveSpeed = 40.f;
	sf::Vector2f posCharacter, prevPosCharacter;
};

