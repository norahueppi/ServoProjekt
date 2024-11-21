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

int ButtonMove180val_last = 0;
int ButtonMove0val_last = 0;     

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

  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe B)
void loop() {
  delay(100);
  ButtonMove180val = digitalRead(BUTTONMOVE180);
  ButtonMove0val = digitalRead(BUTTONMOVE0);

  if((ButtonMove0val != ButtonMove0val_last) && (ButtonMove0val == LOW)){
    servo5.write(0);
  }

  if((ButtonMove180val != ButtonMove180val_last) && (ButtonMove180val == LOW)){
    servo5.write(180);
  }

  ButtonMove0val_last = ButtonMove0val;
  ButtonMove180val_last = ButtonMove180val;
}