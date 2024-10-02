#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO1PIN 8  //Lila
#define SERVO2PIN 11 //Gelb
#define SERVO3PIN 10 //Grün
#define SERVO4PIN 9  //Blau
#define SERVO5PIN 12 //Orange

#define BUTTONPIN1 15
#define BUTTONPIN2 16

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

int Button1val = 0;
int Button2val = 0;

int Button1val_last = 0;
int Button2val_last = 0;

int LEDPin_Blue = 7;
int LEDPin_Green = 6;
int LEDPin_Red = 5;

int stateservo = servostart;
int statebtn = statebegin;

int counter = 0;

int pos = 0;      // position in degrees
ESP32PWM pwm;


void seätup() {
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


/*void loop(){
  delay(20);
  Button1val = digitalRead(BUTTONPIN1);
  if((Button1val != Button1val_last) && (Button1val == LOW)){
    servo5.write(180);
  }
  Button1val_last = Button1val;
}*/

void loop() {
switch (statebtn){
    case statebegin:
      servo1.write(0);
      servo2.write(90);
      servo3.write(90);
      servo4.write(90);
      servo5.write(0);

      digitalWrite(LEDPin_Blue, LOW);
      digitalWrite(LEDPin_Red, LOW);
      digitalWrite(LEDPin_Green, HIGH);

      if((Button1val != Button1val_last) && (Button1val == LOW)){
        statebtn = statebtn1;
        stateservo = servoopen;
      }
      if((Button2val != Button2val_last) && (Button2val == LOW)){
        statebtn = statebtn2;
        stateservo = servoopen;
      }
      Button1val_last = Button1val;
      Button2val_last = Button2val;

      break;

    case statebtn1:
      digitalWrite(LEDPin_Blue, HIGH);
      digitalWrite(LEDPin_Red, LOW);
      digitalWrite(LEDPin_Green, LOW);

      switch(stateservo){
        case servoopen:
          servo1.write(50);
          servo2.write(140);
          servo3.write(20);
          servo4.write(100);
          servo5.write(180);

          counter ++;
          if(counter >= 25){
            stateservo = servoclose;
            counter = 0;
          }

          break;

        case servoclose:
          servo5.write(0);
          if(servo5 == 0){
            counter ++;
            if(counter >= 10)
          }
      }

      break;
  }
}

//Aufgabe a und b
/*void loop() {
  Button1val = digitalRead(BUTTONPIN1);
  Button2val = digitalRead(BUTTONPIN2);

  switch (stateservo){
    case servostart:
      servo1.write(90);
      if((Button1val != Button1val_last) && (Button1val == LOW)){
          stateservo = statebtn1;
      }

      if((Button2val != Button2val_last) && (Button2val == LOW)){
          stateservo = statebtn2;
      }
      digitalWrite(LEDPin_Blue, HIGH);
      digitalWrite(LEDPin_Red, LOW);

      Button1val_last = Button1val;
      Button2val_last = Button2val;
      break;

    case statebtn1:
      servo1.write(90);
      if((Button2val != Button2val_last) && (Button2val == LOW)){
          stateservo = statebtn2;
      }
      digitalWrite(LEDPin_Blue, HIGH);
      digitalWrite(LEDPin_Red, HIGH);

      Button2val_last = Button2val;
      break;

    case statebtn2:
      servo1.write(180);
      if((Button1val != Button1val_last) && (Button1val == LOW)){
          stateservo = statebtn1;
      }
      digitalWrite(LEDPin_Blue, LOW);
      digitalWrite(LEDPin_Red, HIGH);

      Button1val_last = Button1val;
      break;

  }
  delay(100);
  
}*/

//https://github.com/madhephaestus/ESP32Servo/blob/master/examples/Multiple-Servo-Example-Arduino/Multiple-Servo-Example-Arduino.ino
//https://www.arduino.cc/reference/en/
