#include "Game.h"

int main() {
	
	//Random seed
	std::srand(12);

	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Practise", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	
	Game game(&window);
	game.Initialize();
	game.Run();

	return 0;
}
