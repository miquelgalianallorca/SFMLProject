#pragma once

#include "EngineIncludes.h"

class GameState; //Defined in GameState.h

class Game
{
public:
	Game(sf::RenderWindow* window);
	~Game();

	void Initialize();
	void Run();

private:

	void Update(sf::RenderWindow &window, float dt);
	void Draw(sf::RenderWindow &window, float dt);

	sf::RenderWindow& g_Window; //Reference to the window (created in main)
	sf::Vector2f screenCenter;
	sf::Vector2u screenSize;

	sf::Clock g_Clock; //Used in Run loop

	bool g_Ready;
	GameState *g_State;
};
