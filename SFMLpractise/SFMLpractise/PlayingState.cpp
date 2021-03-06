#include "PlayingState.h"


PlayingState::PlayingState()
{
	SetStateName(GAME_STATE::PLAYING);
	level = new Level(50, 30);

	keyClockCounter = 0.f;
	keyClockDelay = 0.3f;
}

PlayingState::~PlayingState()
{
	delete level;
}

void PlayingState::HandleEvent(sf::Event &event) {
	//Handle events in Level
	level->HandleEvent(event);
}

void PlayingState::Update(sf::RenderWindow &window, float deltaTime) {
	//Update level
	level->Update(window, deltaTime);
	//Update view
	UpdateView(window, deltaTime);
}


void PlayingState::UpdateView(sf::RenderWindow &window, float deltaTime) {
	//Zoom view
	//ZoomView(deltaTime);
	
	//Move view
	MoveView(window, deltaTime);
}

void PlayingState::MoveView(sf::RenderWindow &window, float deltaTime) {
	
	prevPosView = mainView.getCenter(); //For interpolation
	
	//World limits
	float worldLimitH = level->GetWorldLimit(true);
	float worldLimitV = level->GetWorldLimit(false);

	if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT)) {
		float viewLimit = window.mapPixelToCoords(sf::Vector2i(mainView.getSize().x, 0)).x;
		if(viewLimit < worldLimitH)
			posView.x += viewMoveSpeed * deltaTime;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_LEFT)) {
		if(window.mapPixelToCoords(sf::Vector2i(0,0)).x > 0)
			posView.x -= viewMoveSpeed * deltaTime;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_UP)) {
		if(window.mapPixelToCoords(sf::Vector2i(0,0)).y > 0)
			posView.y -= viewMoveSpeed * deltaTime;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN)) {
		float viewLimit = window.mapPixelToCoords(sf::Vector2i(0, mainView.getSize().y)).y;
		if(viewLimit < worldLimitV)
			posView.y += viewMoveSpeed * deltaTime;
	}
}

void PlayingState::ZoomView(float deltaTime) {
	keyClockCounter += deltaTime;
	if (keyClockCounter > keyClockDelay) {
		if (Input::IsKeyPressed(Input::KEY::KEY_ADD) || Input::IsKeyPressed(Input::KEY::KEY_SUBTRACT)) {
			zooming = true;
			// Zooming in or out.
			if (Input::IsKeyPressed(Input::KEY::KEY_ADD)) targetZoom = 1.3f;
			else targetZoom = .7f;

			currentZoom = 1.0f;
			previousZoom = currentZoom;
			// Store the current center of the view and our target (the position of the mouse).
			/*currentCenter = App.GetDefaultView().GetCenter();
			targetCenter = App.ConvertCoords(input.GetMouseX(), input.GetMouseY(), &App.GetDefaultView());
			*/
		}
	}
	if (zooming) {
		// Interpolate between the current zoom and the target zoom for a smooth effect.
		currentZoom = Lerp(lerpFactor, currentZoom, targetZoom);
		mainView.zoom(1.0f + (currentZoom - previousZoom));
		//
		//		// Interpolate the between the current center of the view and the target.
		//		/*currentCenter.x = lerp(lerpFactor, currentCenter.x, targetCenter.x);
		//		currentCenter.y = lerp(lerpFactor, currentCenter.y, targetCenter.y);
		//		App.GetDefaultView().SetCenter(currentCenter);
		//		*/

		// Store the previous zoom because we will need the difference between the previous and current zoom.
		// This is because sf::View::Zoom zooms relative to the current zoom.
		previousZoom = currentZoom;

		// If the difference between the current and previous zoom is less then 0.01, stop zooming.
		// Linear interpolation will never reach the target value so we stop here.
		if (fabs(targetZoom - currentZoom) < 0.01f)
			zooming = false;
	}
}

float PlayingState::Lerp(float value, float start, float end) {
	return start + (end - start) * value;
}

void PlayingState::Draw(sf::RenderWindow &window, float alphaInterp) {

	//Interpolate view movement
	sf::Vector2f posViewInterpolated(posView); //Future position
	posViewInterpolated.x = posView.x * alphaInterp + prevPosView.x *(1.0f - alphaInterp);
	posViewInterpolated.y = posView.y * alphaInterp + prevPosView.y *(1.0f - alphaInterp);
	mainView.setCenter(posViewInterpolated);

	//Draw level
	window.setView(mainView);
	level->Draw(window, alphaInterp);
	
	//window.setView(UIView);
	//UI->Draw(window);
}

void PlayingState::ChangeState(GAME_STATE state) {

}

void PlayingState::SetupViews(sf::RenderWindow &window, sf::Vector2f screenCenter) {
	
	//Initialize views
	//currentZoom = 1.f;
	mainView = window.getDefaultView();
	mainView.setCenter(screenCenter);
	posView = mainView.getCenter();
	prevPosView = posView;
	//mainView.zoom(currentZoom);

	UIView = window.getDefaultView();
}