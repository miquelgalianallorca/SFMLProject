#pragma once
#include "EngineIncludes.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	auto GetResource(GraphicsID &graphicsID);

private:
	std::map<GraphicsID, std::shared_ptr<sf::Sprite>> graphicResources; //Key-value pairs

	void LoadGraphicResource(sf::Texture &texture, sf::IntRect rect, GraphicsID graphicsID);
};


//Namespace (Equivalent to C# static class)
//Only one active at the same time. Loads at startup.
namespace RManager {

	ResourceManager resourceManager;

	std::shared_ptr<sf::Sprite> GetResource(GraphicsID &graphicsID);

}