#include "MainMenuState.h"


MainMenuState::MainMenuState()
{
	SetStateName(GAME_STATE::MAIN_MENU);	
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::HandleEvent(sf::Event &event) {

}

void MainMenuState::Update(sf::RenderWindow &window, float deltaTime) {

}

void MainMenuState::Draw(sf::RenderWindow &window, float alphaInterp) {
	
}

void MainMenuState::ChangeState(GAME_STATE state) {

}

void MainMenuState::SetupViews(sf::RenderWindow &window, sf::Vector2f screenCenter) {
	//Initialize views
	mainView = window.getDefaultView();
	mainView.zoom(0.5f);
	UIView = window.getDefaultView();
}