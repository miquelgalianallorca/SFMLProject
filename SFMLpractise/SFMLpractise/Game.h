#pragma once

#include "Player.h"

static float const FPS = 60.0;						// Constant for fixed time - step loop. We'll lock it at 60fps.
static float const MS_PER_STEP = 1.0f / FPS;		// Roughly (0.017) @ 60fps.

class Game
{
public:
	Game(sf::RenderWindow* window);
	~Game();

	void Initialize();
	void Run();

private:
	sf::RenderWindow& g_Window; //Reference to the window (created in main)
	sf::Clock g_Clock; //Used in Run loop
};
