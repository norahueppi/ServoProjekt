#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange


Servo servo5;

int minUs = 1000;
int maxUs = 2000;



int counter = 0;

int Delay = 100;

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


  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe E)
void loop(){
  Button0val = digitalRead(BUTTONPIN0);
  Button1val = digitalRead(BUTTONPIN1);

  if(Button0val == LOW) {
    for(pos; pos >= 180; pos++){
      servo1.write(pos);
      counter++;
      delay(Delay);
      if(counter >= 10){
        counter = 0;
        if(Delay >= 10){
          Delay -= 5;
        }
      }
    }
  }
  else{
    Delay = 100;
  }
  if(Button1val <= LOW) {
    for(pos; pos == 0; pos--){
      servo1.write(pos);
      delay(100);
      counter++;
      delay(Delay);
      if(counter >= 10){
        counter = 0;
        if(Delay >= 10){
          Delay -= 5;
        }
      }
   }
  }
  else{
    Delay = 100;
  }
}