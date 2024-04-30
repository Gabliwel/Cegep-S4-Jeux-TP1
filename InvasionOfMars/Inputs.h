#pragma once
#include <cmath> //abs

struct Inputs
{
	Inputs()
	{
		reset();
	}

	void reset()
	{
		noAngle = false;
		moveVertical = 0.0f;
		moveHorizontal = 0.0f;
		fireMask = false;
		angle = 0.0f;
		//Peut-être pratique de sauvegarder le fait
		//que le gamepad soit actif ou non (voir game.getInputs)
		bool isGamepadActive = false;
	}

	//Portée analogue -100 à 100
	float eliminateVibration(float analogInput)
	{
		if (abs(analogInput) < 20.0f) return 0.0f;
		return analogInput;
	}

	void eliminateDiagonalSpeed()
	{
		if (moveHorizontal != 0.f && moveVertical != 0.f) {
			moveHorizontal /= std::sqrt(2.f);
			moveVertical /= std::sqrt(2.f);
		}
	}

	bool isInPause = false;
	bool isInPauseBuffer = false;
	bool noAngle;
	float moveVertical;
	float moveHorizontal;
	float angle;
	bool isGamepadActive;
	bool fireMask;
};

