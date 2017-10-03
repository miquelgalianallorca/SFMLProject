#include "GroundTile.h"

GroundTile::GroundTile(sf::Color colorFill, sf::Color colorOutline, sf::Vector2f pos, int size) : 
	Tile(colorFill, colorOutline, pos, size)
{
	//Ground graphics
	GraphicsID gId = GraphicsID::Ground;
	//sprite = new sf::Sprite(RManager::GetResource(gId), sf::IntRect(0,0,10,10));
	sprite->setPosition(pos);
}

GroundTile::~GroundTile()
{
}

void GroundTile::Draw(sf::RenderWindow &window) {
	window.draw(*sprite);
}
