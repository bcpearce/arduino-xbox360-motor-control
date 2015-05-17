#include <AFMotor.h>

const uint8_t left_inx = 1;
const uint8_t right_inx = 4;

uint8_t r_spd = 50, l_spd = 50;
uint8_t r_dir = FORWARD, l_dir = BACKWARD;

AF_DCMotor l_motor(left_inx);
AF_DCMotor r_motor(right_inx);

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  l_motor.setSpeed(r_spd);
  r_motor.setSpeed(l_spd);
  l_motor.run(RELEASE);
  r_motor.run(RELEASE);
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() >= 5) {
    digitalWrite(7, HIGH);
    if (Serial.read() == 0x05) {
      l_dir = Serial.read();
      l_spd = Serial.read();
      r_dir = Serial.read();
      r_spd = Serial.read();
      Serial.flush();
    }
  }
  else {
    digitalWrite(7, LOW);
  }
  
  r_motor.run(r_dir);
  l_motor.run(l_dir);
  
  r_motor.setSpeed(r_spd);
  l_motor.setSpeed(l_spd);
  
}
