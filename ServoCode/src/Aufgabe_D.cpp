/* Aufgabe_C.cpp
 by Nora Hüppi
 
 As long as btn0 i spressed the servo rotates from 180° to 0°, if the bt0 is released
 the servo stops rotating.
 If btn1 is pressed and hold the servo rotates back to 180°.
 The servo makes 1° steps in both directions.
  
 Connection of the Servos:
 Servo Datapin (Orange/White) -> Pin12
 Servo Vcc (Red) -> 5V
 Servo GND (Brown) -> GND
 
 Connection of Button Move0:
 3.3V -> PIN15
 
 Connection of Button Move180:
 3.3V -> PIN16
 
 created 28 Oktober 2024
 by Nora Hüppi
 edited 21 November 2024
 by Nora Hüppi
*/

#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange


#define BUTTONPIN0 15
#define BUTTONPIN1 16

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int minUs = 1000;
int maxUs = 2000;


int Button0val = 0;
int Button1val = 0;

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
  
  
  pinMode(BUTTONPIN0, INPUT_PULLUP);
  pinMode(BUTTONPIN1, INPUT_PULLUP);

  pinMode(SERVO5PIN, OUTPUT);

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe D)
void loop() {
  Button0val = digitalRead(BUTTONPIN0);
  Button1val = digitalRead(BUTTONPIN1);
  
  if(Button0val == LOW) {
    for(pos; pos >= 180; pos++){
      servo1.write(pos);
      delay(100);
    }
  }
  else if(Button1val <= LOW) {
    for(pos; pos == 0; pos--){
      servo1.write(pos);
      delay(100);
   }
  }
}