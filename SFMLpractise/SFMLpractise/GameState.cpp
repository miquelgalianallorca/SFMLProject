#include "GameState.h"

GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::SetStateName(GAME_STATE name) {
	stateName = name;
}
GAME_STATE GameState::GetStateName() {
	return stateName;
}