#pragma once

#include "GameState.h"
#include "Level.h"

class PlayingState : public GameState
{
public:
	PlayingState();
	~PlayingState();

	void HandleEvent(sf::Event &event);
	void Update(sf::RenderWindow &window, float deltaTime);
	void Draw(sf::RenderWindow &window, float alphaInterp);

	void ChangeState(GAME_STATE state);
	virtual void SetupViews(sf::RenderWindow &window, sf::Vector2f screenCenter);

private:
	void UpdateView(float deltaTime);
	void MoveView(float deltaTime);
	void ZoomView(float deltaTime);

	//Zoom
	float Lerp(float value, float start, float end);
	sf::Vector2f currentCenter;
	sf::Vector2f targetCenter;
	float targetZoom = 0.0f;
	float currentZoom = 0.0f;
	float previousZoom = 0.0f;
	bool zooming = false;
	float lerpFactor = 0.01f; // The speed of the zooming.
	float keyClockDelay, keyClockCounter;

	//Move
	const float viewMoveSpeed = 200.f;
	sf::Vector2f posView, prevPosView;

	sf::View mainView, UIView;
	Level *level;
};

