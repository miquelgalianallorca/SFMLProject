#pragma once

#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();

	void Update(float frameTime);
	void Draw(float frameTime);

	void ChangeState(GAME_STATE state);
};

