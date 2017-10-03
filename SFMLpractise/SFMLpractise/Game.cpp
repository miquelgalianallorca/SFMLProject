#include "Game.h"

Game::Game(sf::RenderWindow* window) :
	g_Window(*window)
{
	g_Ready = false;

	//Window setup
	g_Window.setVerticalSyncEnabled(true);
	//g_Window.setMouseCursorVisible(false);
	//Calculate and store the center of the screen.
	screenCenter = { g_Window.getSize().x / 2.f, g_Window.getSize().y / 2.f };
	screenSize = g_Window.getSize();
	printf("Screen size x: %i \n", screenSize.x);
	printf("Screen size y: %i \n", screenSize.y);
	//First state
	g_State = new PlayingState();
	g_State->SetupViews(g_Window, screenCenter);

	//// Create the level object.
	//m_level = Level(*window); //THIS IN THE STATE
	//// Create the game font.
	//m_font.loadFromFile("../resources/fonts/ADDSBP__.TTF"); //LOAD RESOURCES
}

Game::~Game()
{
	delete g_State;
}

//Called by main before Run()
void Game::Initialize() {
	
	//...

	//Initialization finished
	std::printf("Game initialized.");
	g_Ready = true;
}

//Main loop
void Game::Run() {

	//GafferonGames Game Loop style
	const float dt = 1.0f / 30.0f; // 30 FPS

	float currentTime = g_Clock.restart().asSeconds();
	float accumulator = 0.f;

	g_Window.setVerticalSyncEnabled(false); //VSync friendly

	//Run the program as long as the window is open
	while (g_Window.isOpen())
	{
		g_Window.clear(); //Clear screen

		//UPDATE
		float newTime = g_Clock.getElapsedTime().asSeconds();
		float frameTime = newTime - currentTime;
		if (frameTime > 0.25f) frameTime = 0.25f; //Avoid "Spiral of Death"
		
		currentTime = newTime;
		accumulator += frameTime;

		//Run update in chunks
		while (accumulator >= dt) {
			Update(g_Window, dt);
			accumulator -= dt;
		}

		const float interpolation = accumulator / dt;
		
		//Draw with interpolation
		Draw(g_Window, interpolation);

		//Update the window
		g_Window.display();
	}

}

void Game::Update(sf::RenderWindow &window, float dt) {
	
	//Process events
	sf::Event event;
	while (g_Window.pollEvent(event))
	{
		//"Close requested" event: we close the window
		if (event.type == sf::Event::Closed || Input::IsKeyPressed(Input::KEY::KEY_ESC)) { //Input is included in Player
			g_Window.close();
			return;
		}

		//Handle other events in states
		g_State->HandleEvent(event);
	}

	//Update game objects
	//if(paused) return;

	g_State->Update(window, dt);
}

void Game::Draw(sf::RenderWindow &window, const float alphaInterp) {

	g_State->Draw(window, alphaInterp);

}