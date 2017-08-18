#pragma once
#include "EngineIncludes.h"

enum class GraphicsID{ Ground, Water, Floor, Rock };

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

	auto GetResource(GraphicsID &graphicsID);

}