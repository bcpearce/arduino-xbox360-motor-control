#ifndef GAMEPAD_H
#define	GAMEPAD_H

#include <Xinput.h>

static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

struct XButtonIDs
{
	XButtonIDs();
	int A, B, X, Y;
	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;
	int L_Shoulder, R_Shoulder;
	int L_Thumbstick, R_Thumbstick;
	int Start, Back;
};

class Gamepad
{
public:
	//Constructors
	Gamepad();
	Gamepad(int a_iIndex);

	void Update();
	void RefreshState();

	//Thumbstick
	bool LStick_InDeadzone();
	bool RStick_InDeadzone();
	short LeftStick_X();
	short LeftStick_Y();
	short RightStick_X();
	short RightStick_Y();

	//Triggers
	BYTE LeftTrigger();
	BYTE RightTrigger();

	//Buttons
	bool GetButtonPressed(int a_iButton);
	bool GetButtonDown(int a_iButton);

	//Utility
	XINPUT_STATE GetState();
	int GetIndex();
	bool Connected();
	void Rumble(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);

private:
	XINPUT_STATE m_State;
	int m_iGamepadIndex;

	static const int ButtonCount = 14;
	bool bPrev_ButtonStates[ButtonCount];
	bool bButtonStates[ButtonCount];

	bool bGamepad_ButtonsDown[ButtonCount];
};

#endif 

extern XButtonIDs XButtons;