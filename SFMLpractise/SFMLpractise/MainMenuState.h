#pragma once

#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();

	void Update(sf::RenderWindow &window, float deltaTime);
	void Draw(sf::RenderWindow &window, float alphaInterp);

	void ChangeState(GAME_STATE state);
	
	void SetupViews(sf::RenderWindow &window, sf::Vector2f screenCenter);

private:
	sf::View mainView, UIView;
};

