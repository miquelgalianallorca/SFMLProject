#include "EngineIncludes.h"
#include "Game.h"


Game::Game(sf::RenderWindow* window) :
	g_Window(*window)
{

}

Game::~Game()
{

}

//Called by main before Run()
void Game::Initialize() {

}

//Main loop
void Game::Run() {

	float currentTime = g_Clock.restart().asSeconds();
	float deltaTime = 0.f;

	//Run the program as long as the window is open
	while (g_Window.isOpen())
	{
		//Check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (g_Window.pollEvent(event))
		{
			//"Close requested" event: we close the window
			if (event.type == sf::Event::Closed || Input::IsKeyPressed(Input::KEY::KEY_ESC)) {
				g_Window.close();
				return;
			}
		}

		//Update clock
		float newTime = g_Clock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		//// Update all items in the level
		//if (!m_levelWasGenerated) {
		//	
		//	Update(frameTime);
		//	// Draw all items in the level.
		//	Draw(frameTime);
		//}
		//else
		//{
		//	m_levelWasGenerated = false;
		//}
	}

}