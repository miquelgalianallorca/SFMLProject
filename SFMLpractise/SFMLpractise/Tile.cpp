#include "Tile.h"

//Empty constructor for initialization
Tile::Tile() {

}

//Constructor with specific colors
Tile::Tile(sf::Color colorFill, sf::Color colorOutline, sf::Vector2f pos, int size):
	tileFilledColor(colorFill),
	tileOutlineColor(colorOutline),
	tilePosition(pos),
	tileSize(size)
{
	SetupRect();
}

//Constructor with default colors
Tile::Tile(sf::Vector2f pos, int size):
	tilePosition(pos),
	tileSize(size)
{
	tileFilledColor = sf::Color::Green;
	tileOutlineColor = sf::Color::Black;
	
	SetupRect();
}

void Tile::SetupRect() {
	//Setup rectangle
	rect.setSize(sf::Vector2f((float)tileSize, (float)tileSize));
	rect.setFillColor(tileFilledColor);
	rect.setOutlineColor(tileOutlineColor);
	rect.setOutlineThickness(1.f);
	rect.setPosition(tilePosition);
}

Tile::~Tile()
{
}

void Tile::Draw(sf::RenderWindow &window) {
	window.draw(rect);
}

//HOVER
void Tile::MarkHover() {
	rect.setFillColor(sf::Color::Red);
}
void Tile::UnmarkHover() {
	if (isSelectedL)
		rect.setFillColor(selectedColorL);
	else if (isSelectedR)
		rect.setFillColor(selectedColorR);
	else
		rect.setFillColor(tileFilledColor); 
}


//CLICK
void Tile::MarkLeftClick() {
	rect.setFillColor(selectedColorL);
	isSelectedL = true;
}
void Tile::MarkRightClick() {
	rect.setFillColor(sf::Color::Yellow);
	isSelectedR = true;
}
void Tile::UnmarkClick() {
	isSelectedL = false;
	isSelectedR = false;
	rect.setFillColor(tileFilledColor);
}

//PATH
void Tile::MarkPath() {
	if (!isSelectedL && !isSelectedR) rect.setFillColor(sf::Color::White);
	isInPath = true;
}
void Tile::UnmarkPath() {
	if(!isSelectedL && !isSelectedR) rect.setFillColor(tileFilledColor);
	isInPath = false;
}
bool Tile::GetIsInPath() {
	return isInPath;
}


sf::Vector2f Tile::GetPosition() {
	return tilePosition;
}