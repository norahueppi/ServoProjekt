#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1;

int minUs = 1000;
int maxUs = 2000;

int servo1Pin = 8;


int pos = 0;      // position in degrees
ESP32PWM pwm;


void setup() {
  // put your setup code here, to run once:
  // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  Serial.begin(9600);
  
  servo1.setPeriodHertz(50);      // Standard 50hz servo
  servo1.attach(servo1Pin, minUs, maxUs);
}

void loop() {
  servo1.write(90);
  delay(20);
  // put your main code here, to run repeatedly:
}

//https://github.com/madhephaestus/ESP32Servo/blob/master/examples/Multiple-Servo-Example-Arduino/Multiple-Servo-Example-Arduino.ino
//https://www.arduino.cc/reference/en/
