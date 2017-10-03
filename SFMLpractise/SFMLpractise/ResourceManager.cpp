#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	//Create map
	//graphicResources

	//Load resources
	sf::Texture texture;
	if (!texture.loadFromFile("../resources/tilemap.png")) {
		//Error
		std::printf("ERROR loading tilemap.png\n");
	}
	else {
		//Load sprites from texture
		std::printf("tilemap.png loaded correctly.\n");
		//FLOOR
		LoadGraphicResource(texture, sf::IntRect(0, 0, 64, 64), GraphicsID::Floor);
		//GROUND
		LoadGraphicResource(texture, sf::IntRect(64, 0, 64, 64), GraphicsID::Ground);
		//WATER
		LoadGraphicResource(texture, sf::IntRect(64 * 2, 0, 64, 64), GraphicsID::Water);
	}


}

void ResourceManager::LoadGraphicResource(sf::Texture &texture, sf::IntRect rect, GraphicsID graphicsID) {
	auto sprite = std::make_shared<sf::Sprite>(sf::Sprite(texture, rect));
	graphicResources.insert(std::pair<GraphicsID, std::shared_ptr<sf::Sprite>>(graphicsID, sprite));
}


ResourceManager::~ResourceManager()
{
}

auto ResourceManager::GetResource(GraphicsID &graphicsID) {
	return graphicResources.at(graphicsID);
}

namespace RManager {
	std::shared_ptr<sf::Sprite> GetResource(GraphicsID &graphicsID) {
		return RManager::resourceManager.GetResource(graphicsID);
	}
}