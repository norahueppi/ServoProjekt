/* Aufgabe_C.cpp
 by Nora Hüppi
 
 If the Servo is on the servo starts to drive to 10 different pointer positions with a 100ms delay.
 Those pointer positions are Predefined.

 Connection of the Servos:
 Servo Datapin (Orange/White) -> Pin12
 Servo Vcc (Red) -> 5V
 Servo GND (Brown) -> GND
 
 Connection of BUTTONMOVE180:
 3.3V -> PIN15
 
 Connection of BUTTONMOVE0:
 3.3V -> PIN16
 
 created 28 Oktober 2024
 by Nora Hüppi
 edited 21 November 2024
 by Nora Hüppi
*/

#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange

Servo servo5;

int LEDPin_Green = 6;

int minUs = 1000;
int maxUs = 2000;

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

  pinMode(LEDPin_Green, OUTPUT);

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe C)
void loop(){ 
  digitalWrite(LEDPin_Green, HIGH);

  delay(3000);
  servo5.write(40);
  delay(1000);
  servo5.write(150);
  delay(1000);
  servo5.write(20);
  delay(1000);
  servo5.write(90);
  delay(1000);
  servo5.write(10);
  delay(1000);
  servo5.write(130);
  delay(1000);
  servo5.write(70);
  delay(1000);
  servo5.write(160);
  delay(1000);
  servo5.write(80);
  delay(1000);
  servo5.write(180);
}