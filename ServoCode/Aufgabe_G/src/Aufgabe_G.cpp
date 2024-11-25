/* Aufgabe_F.cpp
 by Nora Hüppi
 
 If a flank is detected from btn0val than the servos rotate  to a position, pick up a pen and move 
 to another point and let the pen go.
 Is a flank from btn1val detected than the pen will be picked up again and put it on the first poitn.

 Connection of the Servos:
 Servo Datapin (Orange/White) -> Pin12 /Pin11 /Pin10 /Pin9 /Pin8
 Servo Vcc (Red) -> 5V
 Servo GND (Brown) -> GND
 
 Connection of Button0:
 3.3V -> PIN15
 
 Connection of Button1:
 3.3V -> PIN16

 Connection of BUTTONSAVE:
 3.3V -> PIN17

 Connection of BUTTONSTART:
 3.3V -> PIN18

 created 28 Oktober 2024
 by Nora Hüppi
 edited 21 November 2024
 by Nora Hüppi
*/

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

#define servoopen       3
#define servoclose      4
#define servomovestart  5
#define servomove       6
#define servomoveend    7

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int minUs = 1000;
int maxUs = 2000;


int Button0val = 0;
int Button1val = 0;

int Button0val_last = 0;
int Button1val_last = 0;
int Button2val_last = 0;
int Button3val_last = 0;

int LEDPin_Blue = 7;
int LEDPin_Green = 6;
int LEDPin_Red = 5;

int stateservo = servostart;
int statebtn = statebegin;

int statesave = 0;

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

//AUFGABE G)
void loop() {
    delay(100);

    digitalWrite(LEDPin_Blue, LOW);
    digitalWrite(LEDPin_Red, LOW);
    digitalWrite(LEDPin_Green, HIGH);

    Button0val = digitalRead(BUTTONPIN0);
    Button1val = digitalRead(BUTTONPIN1);

    switch (statebtn){
        case statebegin:
            servo1.write(0);
            servo2.write(90);
            servo3.write(90);
            servo4.write(90);
            servo5.write(0);
        
            if((Button0val != Button0val_last) && (Button0val == LOW)){
                statebtn = statebtn1;
                stateservo = servoopen;
            }
            if((Button1val != Button1val_last) && (Button1val == LOW)){
                statebtn = statebtn2;
                stateservo = servomovestart;
            }

            Button0val_last = Button0val;
            Button1val_last = Button1val;

            break;

        case statebtn1:
            digitalWrite(LEDPin_Blue, HIGH);
            digitalWrite(LEDPin_Red, LOW);
            digitalWrite(LEDPin_Green, LOW);

            switch(stateservo){
                case servomovestart:
                    servo1.write(50);
                    delay(15);
                    servo2.write(140);
                    delay(15);
                    servo3.write(20);
                    delay(15);
                    servo4.write(100);
                    delay(15);

                    statesave = 1;

                    stateservo = servoopen;

                    break;

                case servoopen:
                    servo5.write(180);
                    delay(15);

                    if(statesave == 1){
                        statesave = 0;
                        counter ++;
                        if(counter >= 25){
                            stateservo = servoclose;
                            counter = 0;
                        } 
                    }
                    else{
                        statebtn = statebegin;
                    }
                    
                    break;

                case servoclose:
                    servo5.write(0);
                    if(SERVO5PIN >= 0){
                        counter ++;
                        if(counter >= 10){
                            stateservo = servomoveend;
                            counter = 0;
                        }
                    }

                    break;

                case servomove:
                    servo2.write(90);
                    delay(15);
                    servo3.write(90);
                    delay(15);
                    servo4.write(90);
                    delay(15);
                    servo1.write(160);
                    delay(15);
                    
                    stateservo = servomoveend;

                    break;

                case servomoveend:
                    servo1.write(160);
                    delay(15);
                    servo2.write(140);
                    delay(15);
                    servo3.write(20);
                    delay(15);
                    servo4.write(100);
                    delay(15);

                    stateservo = servoopen;

                    break;

            }
        case statebtn2:
            digitalWrite(LEDPin_Blue, LOW);
            digitalWrite(LEDPin_Red, HIGH);
            digitalWrite(LEDPin_Green, LOW);

            switch(stateservo){
                case servomovestart:
                    servo1.write(160);
                    delay(15);
                    servo2.write(140);
                    delay(15);
                    servo3.write(20);
                    delay(15);
                    servo4.write(100);
                    delay(15);

                    stateservo = servoopen;

                    statesave = 1;

                    break;
                
                case servoopen:
                    servo5.write(180);
                    delay(15);

                    if(statesave == 1){
                        statesave = 0;
                        counter ++;
                        if(counter >= 25){
                            stateservo = servoclose;
                            counter = 0;
                        } 
                    }
                    else{
                        statebtn = statebegin;
                    }
                    
                    break;

                case servoclose:
                    servo5.write(0);
                    if(SERVO5PIN >= 0){
                        counter ++;
                        if(counter >= 10){
                            stateservo = servomoveend;
                            counter = 0;
                        }
                    }

                    break;

                case servomove:
                    servo2.write(90);
                    delay(15);
                    servo3.write(90);
                    delay(15);
                    servo4.write(90);
                    delay(15);
                    servo1.write(50);
                    delay(15);
                    
                    stateservo = servomoveend;

                    break;

                case servomoveend:
                    servo1.write(50);
                    delay(15);
                    servo2.write(140);
                    delay(15);
                    servo3.write(20);
                    delay(15);
                    servo4.write(100);
                    delay(15);

                    stateservo = servoopen;

                    break;

            }   
        
    } 
}

