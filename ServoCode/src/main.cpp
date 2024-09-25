#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO1PIN 8
#define SERVO2PIN 11
#define SERVO3PIN 10
#define SERVO4PIN 9
#define SERVO5PIN 12

#define BUTTONPIN1 16
#define BUTTONPIN2 15

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int minUs = 1000;
int maxUs = 2000;

int Button1val = 0;
int Button2val = 0;

int Button1val_last = 0;
int Button2val_last = 0;

int LEDPin_Blue = 7;
int LEDPin_Red = 5;

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
  
  pinMode(BUTTONPIN1, INPUT_PULLUP);
  pinMode(BUTTONPIN2, INPUT_PULLUP);

  pinMode(SERVO1PIN, OUTPUT);
  pinMode(SERVO2PIN, OUTPUT);
  pinMode(SERVO3PIN, OUTPUT);
  pinMode(SERVO4PIN, OUTPUT);
  pinMode(SERVO5PIN, OUTPUT);

  pinMode(LEDPin_Red, OUTPUT);
  pinMode(LEDPin_Blue, OUTPUT);

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

void loop() {
  servo1.write(90);
  servo2.write(180);
  servo3.write(180);
  servo4.write(0);

  Button1val = digitalRead(BUTTONPIN1);

  if((Button1val != Button1val_last) && (Button1val == LOW)){
    servo5.write(90);
    digitalWrite(LEDPin_Blue, HIGH);
    digitalWrite(LEDPin_Red, LOW);
  }
  else{
    servo5.write(80);
    digitalWrite(LEDPin_Blue, LOW);
    digitalWrite(LEDPin_Red, HIGH);
  }

  Button1val_last = Button1val;

  delay(20);
  // put your main code here, to run repeatedly:
}

//https://github.com/madhephaestus/ESP32Servo/blob/master/examples/Multiple-Servo-Example-Arduino/Multiple-Servo-Example-Arduino.ino
//https://www.arduino.cc/reference/en/
