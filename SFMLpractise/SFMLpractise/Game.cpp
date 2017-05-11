#include "EngineIncludes.h"
#include "Game.h"
#include "MainMenuState.h"

Game::Game(sf::RenderWindow* window) :
	g_Window(*window)
{
	g_Ready = false;
	g_State = new MainMenuState();
}

Game::~Game()
{
	delete g_State;
}

//Called by main before Run()
void Game::Initialize() {
	
	//Initialize
	//...

	g_Ready = true;
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
			if (event.type == sf::Event::Closed || Input::IsKeyPressed(Input::KEY::KEY_ESC)) { //Input is included in Player
				g_Window.close();
				return;
			}
		}

		//Update clock
		float newTime = g_Clock.getElapsedTime().asSeconds();
		float frameTime = std::max(0.f, newTime - currentTime);
		currentTime = newTime;

		if (g_Ready) {
			//Update all items
			g_State->Update(frameTime);
			//Draw all items
			g_State->Draw(frameTime);
		}
	}

}
