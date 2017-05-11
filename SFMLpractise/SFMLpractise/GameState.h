#pragma once

enum class GAME_STATE {
	MAIN_MENU,
	PLAYING,
	GAME_OVER
};

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Update(float frameTime) = 0;
	virtual void Draw(float frameTime) = 0;

	void SetStateName(GAME_STATE name);
	GAME_STATE GetStateName();
	virtual void ChangeState(GAME_STATE state) = 0;

private: 
	GAME_STATE stateName;
};

