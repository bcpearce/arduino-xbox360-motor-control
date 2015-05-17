#include <Windows.h>
#include "Gamepad.h"
#include "SerialClass.h"
#include <iostream>
#include <string.h>

#define FORWARD		1
#define BACKWARD	2
#define RELEASE		4

using namespace std;

int get_motor_params(Gamepad hid, unsigned char *l_dir, unsigned char *r_dir, unsigned char *l_spd, unsigned char *r_spd) {
	int r_motor, l_motor;
	if (hid.GetButtonPressed(XButtons.A))
	{
		//use A to quit the interface
		return -1;
	}

	if (hid.RStick_InDeadzone()) {
		r_motor = 0;
	}
	else {
		r_motor = hid.RightStick_Y() * 255 / SHRT_MAX;
	}
	if (hid.LStick_InDeadzone()) {
		l_motor = 0;
	}
	else {
		l_motor = hid.LeftStick_Y() * 255 / SHRT_MAX;
	}

	if (l_motor < 0) {
		l_motor *= -1;
		*l_dir = BACKWARD;
	}
	else if (l_motor == 0) {
		*l_dir = RELEASE;
	}
	else {
		*l_dir = FORWARD;
	}
	if (r_motor < 0) {
		r_motor *= -1;
		*r_dir = BACKWARD;
	}
	else if (r_motor == 0) {
		*r_dir = RELEASE;
	}
	else {
		*r_dir = FORWARD;
	}

	*l_spd = (unsigned char)l_motor;
	*r_spd = (unsigned char)r_motor;
	return 0;
}

int main() {

	Serial *ardu = new Serial("COM4");
	Gamepad *hid = new Gamepad(1);
	unsigned char l_dir, r_dir, l_pow, r_pow;
	unsigned char ardu_msg[5] = {0x05, RELEASE, 0, RELEASE, 0};

	while (1) {
		hid->Update();
		if (get_motor_params(*hid, &l_dir, &r_dir, &l_pow, &r_pow) < 0) {
			break;
		}

		ardu_msg[1] = l_dir;
		ardu_msg[2] = l_pow;
		ardu_msg[3] = r_dir;
		ardu_msg[4] = r_pow;

		ardu->WriteData(ardu_msg, 5);

		cout << l_dir << '\t' << (int)l_pow << '\t';
		cout << r_dir << '\t' << (int)r_pow << endl;

		hid->RefreshState();
	}
	return 0;
}