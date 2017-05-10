#pragma once

class Input
{
public:

	//All possible input keys
	enum class KEY
	{
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_ATTACK,
		KEY_ESC
	};

	//Check if a key is pressed
	static bool IsKeyPressed(KEY keycode);
};
