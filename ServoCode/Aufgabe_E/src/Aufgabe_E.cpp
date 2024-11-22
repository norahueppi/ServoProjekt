/* Aufgabe_E.cpp
 by Nora Hüppi
 
 Like in assigment D the servo rotates vrom 180° t0 0° if btnmove0 is pressed, 
 when realised the servo stops. and vice verca if btnmove180 is pressed an realised.
 it still makes 1° steps in both directions,  just this time the rotation speed goes 
 faster after every 10 repetitions.

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

#define BUTTONMOVE180 15
#define BUTTONMOVE0 16

Servo servo5;

int minUs = 1000;
int maxUs = 2000;

int ButtonMove180val = 0;
int ButtonMove0val = 0;

int LEDPin_Blue = 7;
int LEDPin_Green = 6;
int LEDPin_Red = 5;

int counter = 0;
int Sekundencounter = 0;

int Delay = 200;

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

  pinMode(BUTTONMOVE180, INPUT_PULLUP);
  pinMode(BUTTONMOVE0, INPUT_PULLUP);

  pinMode(SERVO5PIN, OUTPUT);

  pinMode(LEDPin_Red, OUTPUT);
  pinMode(LEDPin_Blue, OUTPUT);
  pinMode(LEDPin_Green, OUTPUT);

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe E)
void loop(){
  ButtonMove180val = digitalRead(BUTTONMOVE180);
  ButtonMove0val = digitalRead(BUTTONMOVE0);

  digitalWrite(LEDPin_Blue, HIGH);
  digitalWrite(LEDPin_Green, LOW);
  digitalWrite(LEDPin_Red,HIGH);

  if(ButtonMove180val == LOW) {
    digitalWrite(LEDPin_Blue, HIGH);
    digitalWrite(LEDPin_Green, LOW);
    digitalWrite(LEDPin_Red,LOW);

    pos++;
    servo5.write(pos);
    Sekundencounter++;
    if(Sekundencounter >= 1000){
      counter++;
    }
    
    delay(Delay);
    if(pos >= 180){
      pos = 180;
    }
    if(counter >= 10){
      if(Delay >= 10){
        Delay -= 10;
      }
      counter = 0;
    }
  }

  if(ButtonMove0val == LOW) {
    digitalWrite(LEDPin_Blue, LOW);
    digitalWrite(LEDPin_Green, LOW);
    digitalWrite(LEDPin_Red,HIGH);

    pos--;
    servo5.write(pos);
    Sekundencounter++;
    if(Sekundencounter >= 1000){
      counter++;
    }
    delay(Delay);
    if(pos <= 0){
      pos = 0;
    }
    if(counter >= 10){
      if(Delay >= 10){
        Delay -= 10;
      }
      counter = 0;
    }
  }
}