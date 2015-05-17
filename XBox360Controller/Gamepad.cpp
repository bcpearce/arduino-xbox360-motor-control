#include <Windows.h>
#include "Gamepad.h"
#include <iostream>

#pragma comment(lib, "Xinput.lib")

XButtonIDs XButtons;

XButtonIDs::XButtonIDs() {
	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 8;

	Start = 10;
	Back = 11;

	L_Thumbstick = 12;
	R_Thumbstick = 13;
}
//Constructors
Gamepad::Gamepad() {}

Gamepad::Gamepad(int a_iIndex)
{
	m_iGamepadIndex = a_iIndex - 1;

	for (int i = 0; i < ButtonCount; i++)
	{
		bPrev_ButtonStates[i] = false;
		bButtonStates[i] = false;
		bGamepad_ButtonsDown[i] = false;
	}
}

XINPUT_STATE Gamepad::GetState()
{
	XINPUT_STATE GamepadState;

	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

	XInputGetState(m_iGamepadIndex, &GamepadState);

	return GamepadState;
}

int Gamepad::GetIndex()
{
	return m_iGamepadIndex;
}

bool Gamepad::Connected()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);

	if (Result == ERROR_SUCCESS)
		return true;
	else
		return false;
}

void Gamepad::Update()
{
	m_State = GetState();

	for (int i = 0; i < ButtonCount; i++) {
		bButtonStates[i] = (m_State.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];
		bGamepad_ButtonsDown[i] = !bPrev_ButtonStates[i] && bButtonStates[i];
	}
}

void Gamepad::RefreshState()
{
	memcpy(bPrev_ButtonStates, bButtonStates, sizeof(bPrev_ButtonStates));
}

bool Gamepad::LStick_InDeadzone()
{
	short sX = m_State.Gamepad.sThumbLX;
	short sY = m_State.Gamepad.sThumbLY;

	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	return true;
}

bool Gamepad::RStick_InDeadzone()
{
	short sX = m_State.Gamepad.sThumbRX;
	short sY = m_State.Gamepad.sThumbRY;

	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	return true;
}

short Gamepad::LeftStick_X()
{
	return m_State.Gamepad.sThumbLX;
	//return (static_cast<float>(sX) / 32768.0f);
}

short Gamepad::LeftStick_Y()
{
	return m_State.Gamepad.sThumbLY;
	//return (static_cast<float>(sY) / 32768.0f);
}

short Gamepad::RightStick_X()
{
	return m_State.Gamepad.sThumbRX;
	//return (static_cast<float>(sX) / 32768.0f);
}

short Gamepad::RightStick_Y()
{
	return m_State.Gamepad.sThumbRY;
	//return (static_cast<float>(sY) / 32768.0f);
}

BYTE Gamepad::RightTrigger()
{
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger;// / 255.0f;
	
	return 0x00;
}

BYTE Gamepad::LeftTrigger()
{
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger;// / 255.0f;

	return 0x00;
}

void Gamepad::Rumble(float a_fLeftMotor, float a_fRightMotor)
{
	XINPUT_VIBRATION VibrationState;

	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	int iLeftMotor = int(a_fLeftMotor * 65535.0f);
	int iRightMotor = int(a_fRightMotor * 65535.0f);

	VibrationState.wLeftMotorSpeed = iLeftMotor;
	VibrationState.wRightMotorSpeed = iRightMotor;

	XInputSetState(m_iGamepadIndex, &VibrationState);
}

bool Gamepad::GetButtonPressed(int a_iButton)
{
	if (m_State.Gamepad.wButtons & XINPUT_Buttons[a_iButton])
	{
		return true;
	}
	return false;
}

bool Gamepad::GetButtonDown(int a_iButton)
{
	return bGamepad_ButtonsDown[a_iButton];
}