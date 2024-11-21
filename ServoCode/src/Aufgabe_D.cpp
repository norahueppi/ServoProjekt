#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO1PIN 8  //Lila
#define SERVO2PIN 11 //Gelb
#define SERVO3PIN 10 //Grün
#define SERVO4PIN 9  //Blau
#define SERVO5PIN 12 //Orange


#define BUTTONPIN0 15
#define BUTTONPIN1 16
#define BUTTONPIN2 17
#define BUTTONPIN3 18

#define servostart  0

#define statebegin  0
#define statebtn1   1
#define statebtn2   2

#define servoopen   3
#define servoclose  4

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int minUs = 1000;
int maxUs = 2000;


int Button0val = 0;
int Button1val = 0;
int Button2val = 0;
int Button3val = 0;


int Button0val_last = 0;
int Button1val_last = 0;
int Button2val_last = 0;
int Button3val_last = 0;

int LEDPin_Blue = 7;
int LEDPin_Green = 6;
int LEDPin_Red = 5;

int stateservo = servostart;
int statebtn = statebegin;

int counter = 0;

int Delay = 100;

int save[10];
int savespace = 0;

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
  pinMode(BUTTONPIN2, INPUT_PULLUP);
  pinMode(BUTTONPIN3, INPUT_PULLUP);

  pinMode(SERVO1PIN, OUTPUT);
  pinMode(SERVO2PIN, OUTPUT);
  pinMode(SERVO3PIN, OUTPUT);
  pinMode(SERVO4PIN, OUTPUT);
  pinMode(SERVO5PIN, OUTPUT);

  pinMode(LEDPin_Red, OUTPUT);
  pinMode(LEDPin_Blue, OUTPUT);
  pinMode(LEDPin_Green, OUTPUT);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  servo4.setPeriodHertz(50);
  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo1.attach(SERVO1PIN, minUs, maxUs);
  servo2.attach(SERVO2PIN, minUs, maxUs);
  servo3.attach(SERVO3PIN, minUs, maxUs);
  servo4.attach(SERVO4PIN, minUs, maxUs);
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