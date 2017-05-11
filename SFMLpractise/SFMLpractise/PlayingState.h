#pragma once

#include "GameState.h"

class PlayingState : public GameState
{
public:
	PlayingState();
	~PlayingState();

	void Update(float frameTime);
	void Draw(float frameTime);

	void ChangeState(GAME_STATE state);
};

