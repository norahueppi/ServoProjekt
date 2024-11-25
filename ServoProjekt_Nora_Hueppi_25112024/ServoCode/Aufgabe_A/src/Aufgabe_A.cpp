/* Aufgabe_A.cpp
 by Nora Hüppi
 
 When the Servo is on, the servo automaticly starts to go to 90°.
 
 Connection of the Servos:
 Servo Datapin (Orange) -> PIN12
 Servo Vcc (Red) -> 5V
 Servo GND (Brown) -> GND
 
 created 28 Oktober 2024
 by Nora Hüppi
 edited 21 November 2024
 by Nora Hüppi
*/

#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange

Servo servo5;

int LEDPin_Blue = 7;

int minUs = 1000;
int maxUs = 2000;

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
  
  pinMode(SERVO5PIN, OUTPUT);

  pinMode(LEDPin_Blue, OUTPUT);

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe A)
void loop() {
  delay(100);
  
  digitalWrite(LEDPin_Blue, HIGH);
  servo5.write(90);
}

//https://github.com/madhephaestus/ESP32Servo/blob/master/examples/Multiple-Servo-Example-Arduino/Multiple-Servo-Example-Arduino.ino
//https://www.arduino.cc/reference/en/






