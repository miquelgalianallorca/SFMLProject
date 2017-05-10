#include "EngineIncludes.h"
#include "Game.h"

using namespace std;

int main() {
	
	//Random seed
	srand(12);

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Practise", sf::Style::Fullscreen);
	Game game(&window);
	game.Initialize();
	game.Run();

	return 0;
}