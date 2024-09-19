#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int minUs = 1000;
int maxUs = 2000;

int servo1Pin = 8;
int servo2Pin = 11;
int servo3Pin = 10;
int servo4Pin = 9;
int servo5Pin = 12;

int Button1Pin = 16;
int Button2Pin = 15;

int Button1val = 0;
int Button2val = 0;



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
  
  pinMode(Button1Pin, INPUT);
  pinMode(Button2Pin, INPUT);

  pinMode(servo1Pin, OUTPUT);
  pinMode(servo2Pin, OUTPUT);
  pinMode(servo3Pin, OUTPUT);
  pinMode(servo4Pin, OUTPUT);
  pinMode(servo5Pin, OUTPUT);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  servo4.setPeriodHertz(50);
  servo5.setPeriodHertz(50);      // Standard 50hz servo

  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
  servo3.attach(servo3Pin, minUs, maxUs);
  servo4.attach(servo4Pin, minUs, maxUs);
  servo5.attach(servo5Pin, minUs, maxUs);
}

void loop() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(0);

  Button1val = digitalRead(Button1Pin);
  Button2val = digitalRead(Button2Pin);

  delay(20);
  // put your main code here, to run repeatedly:
}

//https://github.com/madhephaestus/ESP32Servo/blob/master/examples/Multiple-Servo-Example-Arduino/Multiple-Servo-Example-Arduino.ino
//https://www.arduino.cc/reference/en/
