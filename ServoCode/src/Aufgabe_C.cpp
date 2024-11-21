#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange

Servo servo5;

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

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe C)
void loop(){
  delay(100);
  servo5.write(40);
  delay(100);
  servo5.write(150);
  delay(100);
  servo5.write(20);
  delay(100);
  servo5.write(90);
  delay(100);
  servo5.write(60);
  delay(100);
  servo5.write(30);
  delay(100);
  servo5.write(100);
}