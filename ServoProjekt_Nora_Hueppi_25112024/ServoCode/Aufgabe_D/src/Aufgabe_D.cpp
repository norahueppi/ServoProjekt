/* Aufgabe_D.cpp
 by Nora Hüppi
 
 As long as btn0 i spressed the servo rotates from 180° to 0°, if the bt0 is released
 the servo stops rotating.
 If btn1 is pressed and hold the servo rotates back to 180°.
 The servo makes 1° steps in both directions.

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

#define BUTTONMOVE180 15 //Lila
#define BUTTONMOVE0 16 //Weiss

Servo servo5;

int LEDPin_Blue = 7;
int LEDPin_Red = 5;

int minUs = 1000;
int maxUs = 2000;


int ButtonMove180val = 0;
int ButtonMove0val = 0;

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

  pinMode(LEDPin_Blue, OUTPUT);
  pinMode(LEDPin_Red, OUTPUT);

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe D)
void loop() {
  digitalWrite(LEDPin_Blue, HIGH);
  digitalWrite(LEDPin_Red, HIGH);

  ButtonMove180val = digitalRead(BUTTONMOVE180);
  ButtonMove0val = digitalRead(BUTTONMOVE0);
  
  if(ButtonMove180val == LOW) {
    digitalWrite(LEDPin_Blue, HIGH);
    digitalWrite(LEDPin_Red, LOW);    
    pos++;
    servo5.write(pos);
    delay(15);
    if(pos >= 180){
      pos = 180;
    }
  }
  else if(ButtonMove0val == LOW) {
    digitalWrite(LEDPin_Blue, LOW);
    digitalWrite(LEDPin_Red, HIGH);  
    pos--;
    servo5.write(pos);
    delay(15);
    if(pos <= 0){
      pos = 0;
    }
  }
}