#pragma once

#include "EngineIncludes.h"

enum class GAME_STATE {
	MAIN_MENU,
	PLAYING,
	GAME_OVER
};

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Update(sf::RenderWindow &window, float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow &window, float alphaInterp) = 0;

	void SetStateName(GAME_STATE name);
	GAME_STATE GetStateName();
	virtual void ChangeState(GAME_STATE state) = 0;

	virtual void SetupViews(sf::RenderWindow &window, sf::Vector2f screenCenter) = 0;

private: 
	GAME_STATE stateName;
};

