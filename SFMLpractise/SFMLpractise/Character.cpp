#include "Character.h"
#include "Tile.h"


Character::Character(Tile &startTile):
	currentTile(startTile)
{

	//Sprite
	rect.setFillColor(sf::Color::Green);
	rect.setSize(sf::Vector2f(30, 30));
	rect.setPosition(currentTile.GetPosition());

	posCharacter = rect.getPosition();
}

Character::~Character()
{
}

void Character::Draw(sf::RenderWindow &window, float alphaInterp) {
	
	sf::Vector2f posInterpolated(posCharacter); //Future position
	
	//if(notPaused)
	posInterpolated.x = posCharacter.x * alphaInterp + prevPosCharacter.x *(1.0f - alphaInterp);

	rect.setPosition(posInterpolated);
	window.draw(rect);
}

void Character::Update(float deltaTime) {
	
	prevPosCharacter = posCharacter;
	
	posCharacter.x += moveSpeed * deltaTime;

}